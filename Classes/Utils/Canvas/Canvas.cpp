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

void Canvas::renderizaLinhas(size_t l_ini, size_t l_fim)
{
    Ponto origem_mundo = camera->eye;

    for (size_t l = l_ini; l < l_fim; l++)
    {
        for (size_t c = 0; c < nCol; c++)
        {
            float u = camera->xmin + (camera->xmax - camera->xmin) * (c + 0.5f) / nCol;
            float v = camera->ymax - (camera->ymax - camera->ymin) * (l + 0.5f) / nLin;

            Cor finalColor(0.0f, 0.0f, 0.0f);
            float t_closest = -1.0f;
            Objeto *obj_intersectado = nullptr;

            Ponto pixel_cam(u, v, -camera->d);
            Vetor Dr_cam = normalizar(pixel_cam - Ponto(0, 0, 0));

            Vetor Dr_mundo =
                Dr_cam.Cord_x * camera->right +
                Dr_cam.Cord_y * camera->up +
                Dr_cam.Cord_z * (-camera->forward);

            Dr_mundo = normalizar(Dr_mundo);

            for (Objeto *objeto : objetos)
            {
                if (objeto->raioIntercepta(origem_mundo, Dr_mundo))
                {
                    if (objeto->t_i > 0 && (t_closest < 0 || objeto->t_i < t_closest))
                    {
                        t_closest = objeto->t_i;
                        obj_intersectado = objeto;
                    }
                }
            }

            if (obj_intersectado)
            {
                Ponto P_I = ray(origem_mundo, Dr_mundo, obj_intersectado->t_i);

                finalColor = operadorArroba(obj_intersectado->K_a, Iamb);

                for (Luz *luz : luzes)
                {
                    if (luz->iluminaPonto(P_I) && !obj_intersectado->temSombra(P_I, *luz, obj_intersectado, objetos))
                    {
                        Cor contrib;
                        obj_intersectado->renderiza(contrib, origem_mundo, Dr_mundo, *luz);

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
    }
}

void Canvas::geraImagem()
{
#pragma omp parallel for schedule(dynamic, 16)
    for (size_t l = 0; l < nLin; l += 16)
    {
        size_t l_end = min(l + 16, nLin);
        renderizaLinhas(l, l_end);
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