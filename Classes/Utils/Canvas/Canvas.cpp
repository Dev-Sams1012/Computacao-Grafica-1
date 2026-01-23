#include "Canvas.hpp"

Canvas::Canvas(Janela j, size_t nlin, size_t ncol, Camera *cam, Cor Ia)
{
    this->camera = cam;
    this->janela = j;

    this->nLin = nlin;
    this->nCol = ncol;
    Dx = janela.w / float(nCol);
    Dy = janela.h / float(nLin);

    this->Iamb = Ia;

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

void Canvas::geraImagem(string nomeArquivo)
{
    Ponto origem_mundo = camera->eye;

    for (size_t l = 0; l < nLin; l++)
    {
        for (size_t c = 0; c < nCol; c++)
        {
            float x = -janela.w / 2. + Dx / 2 + float(c) * Dx;
            float y = janela.h / 2. - Dy / 2 - float(l) * Dy;

            Cor finalColor = Cor(0.0f, 0.0f, 0.0f);
            float t_closest = -1.0f;
            Objeto *obj_intersectado = nullptr;

            Ponto pixel_cam = Ponto(x, y, -janela.d);
            Vetor Dr_cam = normalizar(pixel_cam - Ponto(0, 0, 0));

            Vetor Dr_mundo = Dr_cam.Cord_x * camera->right + Dr_cam.Cord_y * camera->up + Dr_cam.Cord_z * (-camera->forward);

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

            if (obj_intersectado != nullptr)
            {
                Ponto P_I = ray(origem_mundo, Dr_mundo, obj_intersectado->t_i);

                Cor ka = obj_intersectado->K_a;
                finalColor = operadorArroba(ka, Iamb);

                for (Luz *luz : luzes)
                {
                    if (luz->iluminaPonto(P_I))
                    {
                        if (!obj_intersectado->temSombra(P_I, *luz, obj_intersectado, objetos))
                        {
                            Cor contrib;
                            obj_intersectado->renderiza(contrib, origem_mundo, Dr_mundo, *luz);

                            finalColor.r += contrib.r;
                            finalColor.g += contrib.g;
                            finalColor.b += contrib.b;
                        }
                    }
                }

                finalColor.r = min(1.0f, finalColor.r);
                finalColor.g = min(1.0f, finalColor.g);
                finalColor.b = min(1.0f, finalColor.b);
            }

            imagem[l * nCol + c] = finalColor;
        }
    }

    ofstream arquivo(nomeArquivo + ".ppm");
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

    cout << "Imagem gerada em " << nomeArquivo << ".ppm'" << endl;
}