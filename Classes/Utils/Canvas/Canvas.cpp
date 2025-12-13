#include "Canvas.hpp"

Canvas::Canvas(Janela j, size_t nlin, size_t ncol, Camera *cam)
{
    this->camera = cam;
    this->janela = j;
    this->nLin = nlin;
    this->nCol = ncol;
    Dx = janela.w / float(nCol);
    Dy = janela.h / float(nLin);
    imagem = vector<vector<Cor>>(nLin, vector<Cor>(nCol));
}

void Canvas::adicionaObjetoCena(Objeto *obj)
{
    objetos.push_back(obj);
}

void Canvas::adicionaLuz(Luz *luz)
{
    luzes.push_back(luz);
}

void Canvas::geraImagem(Luz luz, string nomeArquivo)
{
    Matriz4x4 View = camera->viewMatrix();

    Ponto origem_cam = View * camera->eye;

    for (size_t l = 0; l < nLin; l++)
    {
        for (size_t c = 0; c < nCol; c++)
        {
            float x = -janela.w / 2. + Dx / 2 + float(c) * Dx;
            float y = janela.h / 2. - Dy / 2 - float(l) * Dy;

            Cor finalColor;
            float t_closest = -1.0f;
            Objeto *obj_intersectado = nullptr;

            Ponto canvas_mundo = Ponto(x, y, -janela.d);
            Ponto canvas_cam = View * canvas_mundo;
            Vetor Dr = normalizar(canvas_cam - origem_cam);

            for (Objeto *objeto : objetos)
            {
                if (objeto->raioIntercepta(origem_cam, Dr))
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
                Vetor dir = normalizar(canvas_cam - origem_cam);
                Ponto P_I = ray(origem_cam, dir, obj_intersectado->t_i);

                if (obj_intersectado->temSombra(P_I, luz, obj_intersectado, objetos))
                {
                    float fatorSombra = 0.35f;
                    Cor kd;

                    if (obj_intersectado->temTextura())
                    {
                        kd = obj_intersectado->texturaEm(P_I);
                    }
                    else
                    {
                        kd = obj_intersectado->K_d;
                    }

                    finalColor.r = kd.r * fatorSombra;
                    finalColor.g = kd.g * fatorSombra;
                    finalColor.b = kd.b * fatorSombra;
                }
                else
                {
                    obj_intersectado->renderiza(finalColor, origem_cam, Dr, luz.PF, luz.IF, luz.IA);
                }
            }

            imagem[l][c] = finalColor;
        }
    }

    ofstream arquivo(nomeArquivo + ".ppm");
    arquivo << "P3\n"
            << nCol << " " << nLin << "\n255\n";

    for (size_t l = 0; l < nLin; l++)
    {
        for (size_t c = 0; c < nCol; c++)
        {
            arquivo << imagem[l][c].r * 255 << " " << imagem[l][c].g * 255 << " " << imagem[l][c].b * 255 << " ";
        }

        arquivo << "\n";
    }

    arquivo.close();

    cout << "Imagem gerada em " << nomeArquivo << ".ppm'" << endl;
}