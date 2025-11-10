#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

/* ############################################################## ESTRUTURAS E OPERAÇÕES COM ESTRUTURA ############################################################## */

struct Cor
{
    int r, g, b;
};

struct Ponto
{
    float Cord_x, Cord_y, Cord_z;

    Ponto(float x, float y, float z)
    {
        Cord_x = x;
        Cord_y = y;
        Cord_z = z;
    }
};

struct Vetor
{
    float Cord_x, Cord_y, Cord_z;

    Vetor(float x = 0, float y = 0, float z = 0)
    {
        Cord_x = x;
        Cord_y = y;
        Cord_z = z;
    }
};

/* vetor entre p1 e p2 ( p2 - p1 ) */
Vetor operator-(Ponto p2, Ponto p1)
{
    return Vetor(p2.Cord_x - p1.Cord_x, p2.Cord_y - p1.Cord_y, p2.Cord_z - p1.Cord_z);
}

/* produto escalar de vetores */
float produtoEscalar(Vetor v1, Vetor v2)
{
    return (v1.Cord_x * v2.Cord_x + v1.Cord_y * v2.Cord_y + v1.Cord_z * v2.Cord_z);
}

/* produto componente a componente - normalizado */
Cor operadorArroba(Cor a, Cor b)
{
    return {a.r * b.r / 255, a.g * b.g / 255, a.b * b.b / 255};
}

/* normalização de vetor */
Vetor normalizar(Vetor v)
{
    float norma = sqrtf(v.Cord_x * v.Cord_x + v.Cord_y * v.Cord_y + v.Cord_z * v.Cord_z);
    return Vetor(v.Cord_x / norma, v.Cord_y / norma, v.Cord_z / norma);
}

/* inverter sentido de vetor */
Vetor operator-(Vetor v)
{
    return Vetor(-v.Cord_x, -v.Cord_y, -v.Cord_z);
}

/* ############################################################## VARIÁVEIS GLOBAIS ############################################################## */

/* origem do Observador */
Ponto origem = Ponto(0, 0, 0);

/* janela Real */
float wJanela = 2.0f;
float hJanela = 2.0f;
float dJanela = 1.0f;

/* esfera */
float rEsfera = 0.5f;
float zEsfera = -(dJanela + rEsfera);
Cor esfColor = {255, 0, 0};

/* centro da esfera */
Ponto centroEsfera = Ponto(0, 0, zEsfera);

/* direção do raio: esfera -> origem */
Vetor w = origem - centroEsfera;

/* cor de fundo [ cinza ] */
Cor bgColor = {100, 100, 100};

/* intensidade da fonte pontual */
Cor I_F_cor = {179, 179, 179};

/* propriedades do material */
Cor K_d = {255, 0, 0};
Cor K_s = {255, 255, 255};
int m = 10;

/* posição da fonte pontual situada a 5 metros acima do olho do observador. */
Ponto P_F = Ponto(0, 5, 0);

/* canvas pixels: size_t pois não há valores negativos ( e tirar o warning ) */
size_t nCol = 1000;
size_t nLin = 1000;

/* tamanho dos pixels */
float Dx = wJanela / float(nCol);
float Dy = hJanela / float(nLin);

/* ############################################################## FUNÇÕES ############################################################## */

bool RaioInterceptaEsfera(float x, float y, float &t_i, Vetor &Dr)
{

    /* ponto do canvas */
    Ponto canvas = Ponto(x, y, -dJanela);

    /* direção do raio: origem -> canvas */
    Vetor Dr_local = canvas - origem;

    Dr = normalizar(Dr_local);

    /* aplicando o raio na equação da esfera */
    float a = produtoEscalar(Dr, Dr);
    float b = 2 * (produtoEscalar(w, Dr));
    float c = produtoEscalar(w, w) - rEsfera * rEsfera;

    /* bhaskara para verificar se o raio bate na esfera ou não */
    float delta = powf(b, 2) - 4 * a * c;
    if (delta < 0)
        return false;

    float r1 = (-b + sqrt(delta)) / (2 * a);
    float r2 = (-b - sqrt(delta)) / (2 * a);

    float t;

    if (r1 > 0 && r2 > 0)
    {
        if (r1 <= r2)
            t = r1;
        else
            t = r2;
    }
    else if (r1 > 0)
    {
        t = r1;
    }
    else if (r2 > 0)
    {
        t = r2;
    }
    else
    {
        return false;
    }

    t_i = t;

    return true;
}

/* ############################################################## MAIN ############################################################## */

int main()
{

    /* matriz 2d: imagem */
    vector<vector<Cor>> imagem(nLin, vector<Cor>(nCol, bgColor));

    for (size_t l = 0; l < nLin; l++)
    {
        for (size_t c = 0; c < nCol; c++)
        {
            float x = -wJanela / 2. + Dx / 2 + float(c) * Dx;
            float y = hJanela / 2. - Dy / 2 - float(l) * Dy;

            float t_i;
            Vetor Dr;

            if (RaioInterceptaEsfera(x, y, t_i, Dr))
            {

                Ponto P_I(origem.Cord_x + t_i * Dr.Cord_x, origem.Cord_y + t_i * Dr.Cord_y, origem.Cord_z + t_i * Dr.Cord_z);

                Vetor n = normalizar(P_I - centroEsfera);

                Vetor l_vetor = normalizar(P_F - P_I);

                Vetor v = -Dr;

                float ln = produtoEscalar(l_vetor, n);
                Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

                /* componente difusa */
                Cor I_diff = operadorArroba(K_d, I_F_cor);
                float diff = max(0.0f, ln);
                I_diff.r = int(I_diff.r * diff);
                I_diff.g = int(I_diff.g * diff);
                I_diff.b = int(I_diff.b * diff);

                /* componente especular */
                Cor I_espec = operadorArroba(K_s, I_F_cor);
                float vr = max(0.0f, produtoEscalar(v, r));
                float espec = powf(vr, m);
                I_espec.r = int(I_espec.r * espec);
                I_espec.g = int(I_espec.g * espec);
                I_espec.b = int(I_espec.b * espec);

                /* cor final */
                Cor finalColor;
                finalColor.r = min(255, I_diff.r + I_espec.r);
                finalColor.g = min(255, I_diff.g + I_espec.g);
                finalColor.b = min(255, I_diff.b + I_espec.b);

                imagem[l][c] = finalColor;
            }
        }
    }

    /* "conversão" da matriz 2d para uma imagem ppm */
    ofstream arquivo("imagem_esfera_iluminada.ppm");
    arquivo << "P3\n"
            << nCol << " " << nLin << "\n255\n";

    for (size_t l = 0; l < nLin; l++)
    {
        for (size_t c = 0; c < nCol; c++)
        {
            arquivo << imagem[l][c].r << " " << imagem[l][c].g << " " << imagem[l][c].b << " ";
        }

        arquivo << "\n";
    }

    arquivo.close();

    cout << "Imagem gerada em 'imagem_esfera_iluminada.ppm'" << endl;

    return 0;
}
