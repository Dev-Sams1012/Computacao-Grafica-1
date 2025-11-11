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

bool Canvas::temSombra(Ponto P_I, Luz luz, Objeto *objeto_atual)
{
    Vetor L = luz.PF - P_I;
    float distancia_Pi_Pf = sqrtf(produtoEscalar(L, L));
    if (distancia_Pi_Pf <= 0.0f)
        return false;

    Vetor L_dir = normalizar(L);
    float epsilon = 0.001f;

    Ponto Ponto_Luz = ray(P_I, L_dir, distancia_Pi_Pf);

    for (Objeto *objeto : objetos)
    {
        if (objeto != objeto_atual)
        {
            if (objeto->raioIntercepta(P_I, Ponto_Luz))
            {
                if (objeto->t_i > epsilon && objeto->t_i < distancia_Pi_Pf)
                {
                    return true;
                }
            }
        }
    }

    return false;
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

                        if (temSombra(P_I, luz, objeto))
                        {
                            finalColor = operadorArroba(objeto->K_a, luz.IA);
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
    arquivo << "P3\n" << nCol << " " << nLin << "\n255\n";

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