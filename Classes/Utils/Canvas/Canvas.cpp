#include "Canvas.hpp"
#include <omp.h>

Canvas::Canvas(string nome, Janela j, size_t nlin, size_t ncol, Camera *cam, Cor Ia)
{
    this->camera = cam;
    this->janela = j;

    this->nLin = nlin;
    this->nCol = ncol;
    Dx = janela.w / float(nCol);
    Dy = janela.h / float(nLin);

    this->Iamb = Ia;

    this->nomeArquivoSaida = nome;

    imagem = vector<Cor>(nLin * nCol, Cor(0, 0, 0));
}

void Canvas::adicionaObjetoCena(Objeto *obj)
{
    objetos.push_back(obj);
}

void Canvas::adicionaLuz(Luz *luz)
{
    luzes.push_back(luz);
}

void Canvas::geraImagem()
{
    Camera* cam = camera;
    const auto& objs = objetos;
    const auto& luzs = luzes;

#pragma omp parallel for collapse(2) schedule(dynamic)
    for (size_t l = 0; l < nLin; ++l)
    for (size_t c = 0; c < nCol; ++c)
    {
        float u = cam->xmin + (cam->xmax - cam->xmin) * (c + 0.5f) / nCol;
        float v = cam->ymax - (cam->ymax - cam->ymin) * (l + 0.5f) / nLin;

        Cor finalColor(0,0,0);

        Ponto pixel_cam(u, v, -cam->d);
        Vetor Dr_cam = normalizar(pixel_cam - Ponto(0, 0, 0));
        Vetor Dr =
            Dr_cam.Cord_x * cam->right +
            Dr_cam.Cord_y * cam->up +
            Dr_cam.Cord_z * (-cam->forward);

        Dr = normalizar(Dr);

        HitInfo hit;
        hit.t = INFINITY;

        for (Objeto* obj : objs)
            obj->raioIntercepta(cam->eye, Dr, hit);

        if (hit.objeto)
        {
            finalColor = operadorArroba(hit.objeto->K_a, Iamb);

            for (Luz* luz : luzs)
            {
                if (luz->iluminaPonto(hit.ponto) &&
                    !hit.objeto->temSombra(hit, *luz, objs))
                {
                    Cor contrib;
                    hit.objeto->renderiza(contrib, hit, *luz);
                    finalColor.r += contrib.r;
                    finalColor.g += contrib.g;
                    finalColor.b += contrib.b;
                }
            }

                finalColor.r = min(1.0f, finalColor.r);
                finalColor.g = min(1.0f, finalColor.g);
                finalColor.b = min(1.0f, finalColor.b);
            }

        imagem[l * nCol + c] = finalColor;
    }

    ofstream arquivo(nomeArquivoSaida + ".ppm");
    arquivo << "P3\n"
            << nCol << " " << nLin << "\n255\n";

    for (size_t l = 0; l < nLin; l++)
    {
        for (size_t c = 0; c < nCol; c++)
        {
            Cor &pixel = imagem[l * nCol + c];

            arquivo << pixel.r * 255 << " "
                    << pixel.g * 255 << " "
                    << pixel.b * 255 << " ";
        }
        arquivo << "\n";
    }

    arquivo.close();

    cout << "Imagem gerada em " << nomeArquivoSaida << ".ppm'" << endl;
}

Objeto *Canvas::pick(int x, int y)
{
    float u = camera->xmin + (camera->xmax - camera->xmin) * (x + 0.5f) / nCol;
    float v = camera->ymax - (camera->ymax - camera->ymin) * (y + 0.5f) / nLin;

    Ponto origem = camera->eye;

    Ponto pixel_cam(u, v, -camera->d);
    Vetor Dr_cam = normalizar(pixel_cam - Ponto(0.0f, 0.0f, 0.0f));
    Vetor Dr =
        Dr_cam.Cord_x * camera->right +
        Dr_cam.Cord_y * camera->up +
        Dr_cam.Cord_z * (-camera->forward);

    Dr = normalizar(Dr);

    HitInfo hit;

    for (Objeto *obj : objetos)
        obj->raioIntercepta(origem, Dr, hit);

    return hit.objeto;
}