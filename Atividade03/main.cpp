#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

/* ############################################################## ESTRUTURAS E OPERAÇÕES COM ESTRUTURA ############################################################## */

struct Cor
{
    float r, g, b;

    Cor(float r = 0.0f, float g = 0.0f, float b = 0.0f)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
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
    return {a.r * b.r, a.g * b.g, a.b * b.b};
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
float wJanela = 0.6f;
float hJanela = 0.6f;
float dJanela = 0.3f;

/* esfera */
float rEsfera = 0.4f;
float zEsfera = -(dJanela + rEsfera);
Ponto centroEsfera = Ponto(0.0f, 0.0f, -1.0f);

/* propriedades da esfera */
Cor K_d_esfera = Cor(0.7f, 0.2f, 0.2f);
Cor K_e_esfera = Cor(0.7f, 0.2f, 0.2f);
Cor K_a_esfera = Cor(0.7f, 0.2f, 0.2f);
int m_esfera = 10;

/* plano do chão */
Ponto P_pi_chao = Ponto(0.0f, -rEsfera, 0.0f);
Vetor n_bar_chao = Vetor(0.0f, 1.0f, 0.0f);

/* propriedades do plano do chão */
Cor K_d_chao = Cor(0.2f, 0.7f, 0.2f);
Cor K_a_chao = Cor(0.2f, 0.7f, 0.2f);
Cor K_e_chao = Cor(0.0f, 0.0f, 0.0f);
int m_chao = 1;

/* plano de fundo */
Ponto P_pi_fundo = Ponto(0.0f, 0.0f, -2.0f);
Vetor n_bar_fundo = Vetor(0.0f, 0.0f, 1.0f);

/* propriedades do plano do chão */
Cor K_d_fundo = Cor(0.3f, 0.3f, 0.7f);
Cor K_a_fundo = Cor(0.3f, 0.3f, 0.7f);
Cor K_e_fundo = Cor(0.0f, 0.0f, 0.0f);
int m_fundo = 1;

/* direção do raio: esfera -> origem */
Vetor w = origem - centroEsfera;

/* Luz */
Cor I_F = Cor(0.7f, 0.7f, 0.7f);
Ponto P_F = Ponto(0.0f, 0.6f, -0.3f);
Cor I_A = Cor(0.3f, 0.3f, 0.3f);

/* canvas pixels: size_t pois não há valores negativos ( e tirar o warning ) */
size_t nCol = 500;
size_t nLin = 500;

/* tamanho dos pixels */
float Dx = wJanela / float(nCol);
float Dy = hJanela / float(nLin);

/* epsilon para comparação de floats */
float EPS = 1e-6f;

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

bool RaioInterceptaPlano(float x, float y, float &t_i, Vetor &Dr, Ponto P_pi, Vetor n_bar)
{
    /* ponto do canvas */
    Ponto canvas = Ponto(x, y, -dJanela);

    /* direção do raio: origem -> canvas */
    Vetor Dr_local = canvas - origem;

    Dr = normalizar(Dr_local);

    float denom = produtoEscalar(Dr, n_bar);
    if (fabs(denom) > EPS) /* comparação com epsilon, para evitar divisão por zero */
    {
        /* equação do raio aplicado ao plano */
        Vetor w = P_pi - origem;
        float t = produtoEscalar(w, n_bar) / denom; 

        if (t > 0)
        {
            t_i = t;
            return true;
        }
    }

    return false;
}

bool TemSombraComEsfera(Ponto P_I, Ponto P_F)
{
    /* direção do raio: origem -> luz */
    Vetor L = P_F - P_I;
    float distancia_Pi_Pf = sqrtf(produtoEscalar(L, L));
    Vetor L_dir = normalizar(L);

    /* desloca o ponto de origem um pouco na direção da luz para evitar self-intersection */
    Ponto P_origem_sombra = Ponto(
        P_I.Cord_x + EPS * L_dir.Cord_x,
        P_I.Cord_y + EPS * L_dir.Cord_y,
        P_I.Cord_z + EPS * L_dir.Cord_z);

    /* verifica se o raio a partir de P_I até a luz intercepta a esfera */
    Vetor OC = P_origem_sombra - centroEsfera;

    float a = produtoEscalar(L_dir, L_dir);
    float b = 2 * produtoEscalar(OC, L_dir);
    float c = produtoEscalar(OC, OC) - rEsfera * rEsfera;

    float delta = powf(b, 2) - 4 * a * c;
    if (delta < 0)
        return false;

    float t1 = (-b - sqrt(delta)) / (2 * a);
    float t2 = (-b + sqrt(delta)) / (2 * a);

    /* verifica se intercepta a esfera antes de chegar na luz */
    if ((t1 > 0 && t1 < distancia_Pi_Pf) || (t2 > 0 && t2 < distancia_Pi_Pf))
        return true;

    return false;
}

/* ############################################################## MAIN ############################################################## */

int main()
{

    /* matriz 2d: imagem */
    vector<vector<Cor>> imagem(nLin, vector<Cor>(nCol));

    for (size_t l = 0; l < nLin; l++)
    {
        for (size_t c = 0; c < nCol; c++)
        {
            float x = -wJanela / 2. + Dx / 2 + float(c) * Dx;
            float y = hJanela / 2. - Dy / 2 - float(l) * Dy;

            float t_i_esfera, t_i_chao, t_i_fundo;
            Vetor Dr_esfera, Dr_chao, Dr_fundo;

            Cor finalColor;
            float t_closest = -1.0f; /* valor invalido para ser alterado depois */

            if (RaioInterceptaEsfera(x, y, t_i_esfera, Dr_esfera))
            {

                if (t_i_esfera > 0 && (t_closest < 0 || t_i_esfera < t_closest))
                {
                    t_closest = t_i_esfera; 

                    /* ponto de interseção */
                    Ponto P_I = Ponto(origem.Cord_x + t_i_esfera * Dr_esfera.Cord_x, origem.Cord_y + t_i_esfera * Dr_esfera.Cord_y, origem.Cord_z + t_i_esfera * Dr_esfera.Cord_z);

                    /* normal do ponto de interseção */
                    Vetor n = normalizar(P_I - centroEsfera);

                    /* vetor direção da luz */
                    Vetor l_vetor = normalizar(P_F - P_I);

                    /* vetor direção do observador */
                    Vetor v = -Dr_esfera;

                    float ln = produtoEscalar(l_vetor, n);

                    /* vetor reflexão */
                    Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

                    /* componente difusa */
                    Cor I_diff = operadorArroba(K_d_esfera, I_F);
                    float diff = max(0.0f, ln);
                    I_diff.r = I_diff.r * diff;
                    I_diff.g = I_diff.g * diff;
                    I_diff.b = I_diff.b * diff;

                    /* componente especular */
                    Cor I_espec = operadorArroba(K_e_esfera, I_F);
                    float vr = max(0.0f, produtoEscalar(v, r));
                    float espec = powf(vr, m_esfera);
                    I_espec.r = I_espec.r * espec;
                    I_espec.g = I_espec.g * espec;
                    I_espec.b = I_espec.b * espec;

                    /* componente ambiente */
                    Cor I_amb = operadorArroba(K_a_esfera, I_A);

                    finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
                    finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
                    finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
                }
            }

            if (RaioInterceptaPlano(x, y, t_i_fundo, Dr_fundo, P_pi_fundo, n_bar_fundo))
            {

                if (t_i_fundo > 0 && (t_closest < 0 || t_i_fundo < t_closest))
                {
                    t_closest = t_i_fundo;

                    /* ponto de interseção */
                    Ponto P_I = Ponto(origem.Cord_x + t_i_fundo * Dr_fundo.Cord_x, origem.Cord_y + t_i_fundo * Dr_fundo.Cord_y, origem.Cord_z + t_i_fundo * Dr_fundo.Cord_z);


                    if (TemSombraComEsfera(P_I, P_F)) /* verifica se intercepta a esfera antes de chegar na luz */
                    {
                        finalColor = operadorArroba(K_a_fundo, I_A);
                    }
                    else
                    {
                        /* normal do ponto de interseção */
                        Vetor n = n_bar_fundo;

                        /* vetor direção da luz */
                        Vetor l_vetor = normalizar(P_F - P_I);
                        
                        /* vetor direção do observador */
                        Vetor v = -Dr_fundo;

                        float ln = produtoEscalar(l_vetor, n);
                        
                        /* vetor reflexão */
                        Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

                        /* componente difusa */
                        Cor I_diff = operadorArroba(K_d_fundo, I_F);
                        float diff = max(0.0f, ln);
                        I_diff.r = I_diff.r * diff;
                        I_diff.g = I_diff.g * diff;
                        I_diff.b = I_diff.b * diff;

                        /* componente especular */
                        Cor I_espec = operadorArroba(K_e_fundo, I_F);
                        float vr = max(0.0f, produtoEscalar(v, r));
                        float espec = powf(vr, m_esfera);
                        I_espec.r = I_espec.r * espec;
                        I_espec.g = I_espec.g * espec;
                        I_espec.b = I_espec.b * espec;

                        /* componente ambiente */
                        Cor I_amb = operadorArroba(K_a_fundo, I_A);

                        finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
                        finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
                        finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
                    }
                }
            }

            if (RaioInterceptaPlano(x, y, t_i_chao, Dr_chao, P_pi_chao, n_bar_chao))
            {

                if (t_i_chao > 0 && (t_closest < 0 || t_i_chao < t_closest))
                {
                    t_closest = t_i_chao;

                    Ponto P_I = Ponto(origem.Cord_x + t_i_chao * Dr_chao.Cord_x, origem.Cord_y + t_i_chao * Dr_chao.Cord_y, origem.Cord_z + t_i_chao * Dr_chao.Cord_z);

                    if (TemSombraComEsfera(P_I, P_F))
                    {
                        finalColor = operadorArroba(K_a_chao, I_A);
                    }
                    else
                    {
                        /* normal do ponto de interseção */
                        Vetor n = n_bar_chao;

                        /* vetor direção da luz */
                        Vetor l_vetor = normalizar(P_F - P_I);
                        
                        /* vetor direção do observador */
                        Vetor v = -Dr_chao;

                        float ln = produtoEscalar(l_vetor, n);
                        
                        /* vetor reflexão */
                        Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

                        /* componente difusa */
                        Cor I_diff = operadorArroba(K_d_chao, I_F);
                        float diff = max(0.0f, ln);
                        I_diff.r = I_diff.r * diff;
                        I_diff.g = I_diff.g * diff;
                        I_diff.b = I_diff.b * diff;

                        /* componente especular */
                        Cor I_espec = operadorArroba(K_e_chao, I_F);
                        float vr = max(0.0f, produtoEscalar(v, r));
                        float espec = powf(vr, m_esfera);
                        I_espec.r = I_espec.r * espec;
                        I_espec.g = I_espec.g * espec;
                        I_espec.b = I_espec.b * espec;

                        /* componente ambiente */
                        Cor I_amb = operadorArroba(K_a_chao, I_A);

                        finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
                        finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
                        finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
                    }
                }
            }

            imagem[l][c] = finalColor;
        }
    }

    /* "conversão" da matriz 2d para uma imagem ppm */
    ofstream arquivo("imagem_esfera_iluminada_e_plano.ppm");
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

    cout << "Imagem gerada em 'imagem_esfera_iluminada_e_plano.ppm'" << endl;

    return 0;
}