#include "Canvas.hpp"

Canvas::Canvas(Janela j, size_t nlin, size_t ncol, Ponto origem)
{
    this->origem = origem;
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

void Canvas::geraImagem(Luz luz, string nomeArquivo)
{
    for (size_t l = 0; l < nLin; l++)
    {
        for (size_t c = 0; c < nCol; c++)
        {
            float x = -janela.w / 2. + Dx / 2 + float(c) * Dx;
            float y = janela.h / 2. - Dy / 2 - float(l) * Dy;

            Cor finalColor;
            float t_closest = -1.0f;

            Ponto canvas = Ponto(x, y, -janela.d);

            for (Objeto *objeto : objetos)
            {
                if (objeto->raioIntercepta(origem, canvas))
                {
                    if (objeto->t_i > 0 && (t_closest < 0 || objeto->t_i < t_closest))
                    {
                        t_closest = objeto->t_i;

                        Ponto P_I = ray(origem, objeto->Dr, objeto->t_i);

                        if (objeto->temSombra(P_I, luz, objeto, objetos))
                        {
                            float fatorSombra = 0.35f;

                            Cor kd;

                            if (objeto->temTextura())
                            {
                                kd = objeto->texturaEm(P_I);
                            }
                            else
                            {
                                kd = objeto->K_d;
                            }

                            finalColor.r = kd.r * fatorSombra;
                            finalColor.g = kd.g * fatorSombra;
                            finalColor.b = kd.b * fatorSombra;
                        }
                        else
                        {
                            objeto->renderiza(finalColor, origem, luz.PF, luz.IF, luz.IA);
                        }
                    }
                }
            }

            imagem[l][c] = finalColor;
        }
    }

    /* "conversão" da matriz 2d para uma imagem ppm */
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