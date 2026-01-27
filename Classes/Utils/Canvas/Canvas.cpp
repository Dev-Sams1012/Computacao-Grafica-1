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
    Camera camLocal = *camera;
    const auto &objs = objetos;
    const auto &luzs = luzes;

#pragma omp parallel for collapse(2) schedule(dynamic)
    for (size_t l = 0; l < nLin; ++l)
        for (size_t c = 0; c < nCol; ++c)
        {
            float u = camLocal.xmin + (camLocal.xmax - camLocal.xmin) * (c + 0.5f) / nCol;
            float v = camLocal.ymax - (camLocal.ymax - camLocal.ymin) * (l + 0.5f) / nLin;

            Cor finalColor(0, 0, 0);

            Ponto origemRaio;
            Vetor Dr;

            if (camLocal.tipo == Camera::PERSPECTIVA)
            {
                origemRaio = camLocal.eye;
                Ponto pixel_cam(u, v, -camLocal.d);
                Vetor Dr_cam = normalizar(pixel_cam - Ponto(0, 0, 0));
                Dr = Dr_cam.Cord_x * camLocal.right + Dr_cam.Cord_y * camLocal.up + Dr_cam.Cord_z * (-camLocal.forward);
            }
            else
            {
                origemRaio = camLocal.eye + (camLocal.right * u) + (camLocal.up * v);
                if (camLocal.tipo == Camera::ORTOGRAFICA)
                    Dr = camLocal.forward;
                else
                {
                    float k = 0.70710678f;
                    Dr = camLocal.forward + k * camLocal.right + k * camLocal.up;
                }
            }

            Dr = normalizar(Dr);

            HitInfo hit;
            hit.t = INFINITY;

            for (Objeto *obj : objs)
                obj->raioIntercepta(origemRaio, Dr, hit);

            if (hit.objeto)
            {
                finalColor = operadorArroba(hit.objeto->K_a, Iamb);

                Cor corObjeto = hit.objeto->temTextura() ? hit.objeto->texturaEm(hit.ponto) : hit.objeto->K_d;

                finalColor = operadorArroba(finalColor, corObjeto);

                for (Luz *luz : luzs)
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

    cout << "Imagem gerada" << endl;
}

Objeto *Canvas::pick(int x, int y)
{
    float u = camera->xmin + (camera->xmax - camera->xmin) * (x + 0.5f) / nCol;
    float v = camera->ymax - (camera->ymax - camera->ymin) * (y + 0.5f) / nLin;

    Ponto origemRaio;
    Vetor Dr;

    if (camera->tipo == Camera::PERSPECTIVA)
    {
        origemRaio = camera->eye;
        Ponto pixel_cam(u, v, -camera->d);
        Vetor Dr_cam = normalizar(pixel_cam - Ponto(0, 0, 0));
        Dr = Dr_cam.Cord_x * camera->right + Dr_cam.Cord_y * camera->up + Dr_cam.Cord_z * (-camera->forward);
    }
    else
    {
        origemRaio = camera->eye + (camera->right * u) + (camera->up * v);
        if (camera->tipo == Camera::ORTOGRAFICA)
            Dr = camera->forward;
        else
        {
            float k = 0.70710678f;
            Dr = camera->forward + k * camera->right + k * camera->up;
        }
    }

    Dr = normalizar(Dr);
    HitInfo hit;
    hit.t = INFINITY;

    for (Objeto *obj : objetos)
        obj->raioIntercepta(origemRaio, Dr, hit);

    return hit.objeto;
}