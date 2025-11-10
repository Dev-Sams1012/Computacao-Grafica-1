#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

/* ############################################################## ESTRUTURAS E OPERAÇÕES COM ESTRUTURA ############################################################## */

struct Janela
{
    float w, h, d;

    Janela(float w = 0.0f, float h = 0.0f, float d = 0.0f)
    {
        this->w = w;
        this->h = h;
        this->d = d;
    }
};

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

/* produto componente a componente - normalizado */
Cor operadorArroba(Cor a, Cor b)
{
    return {a.r * b.r, a.g * b.g, a.b * b.b};
}

struct Ponto
{
    float Cord_x, Cord_y, Cord_z;

    Ponto(float x = 0, float y = 0, float z = 0)
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

Vetor operator-(Vetor v1, Vetor v2)
{
    return Vetor(v1.Cord_x - v2.Cord_x, v1.Cord_y - v2.Cord_y, v1.Cord_z - v2.Cord_z);
}

Ponto operator+(Ponto p1, Ponto p2)
{
    return Ponto(p1.Cord_x + p2.Cord_x, p1.Cord_y + p2.Cord_y, p1.Cord_z + p2.Cord_z);
}

/* produto escalar de vetores */
float produtoEscalar(Vetor v1, Vetor v2)
{
    return (v1.Cord_x * v2.Cord_x + v1.Cord_y * v2.Cord_y + v1.Cord_z * v2.Cord_z);
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

/* multiplicação escalar por vetor (float * Vetor) */
Vetor operator*(float k, const Vetor &v)
{
    return Vetor(k * v.Cord_x, k * v.Cord_y, k * v.Cord_z);
}

Ponto ray(Ponto p, Vetor v, float t)
{
    return Ponto(p.Cord_x + v.Cord_x * t,
                 p.Cord_y + v.Cord_y * t,
                 p.Cord_z + v.Cord_z * t);
}

struct Matriz3x3
{
    float m[3][3];

    Matriz3x3(float diag = 0.0f)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (i == j)
                    m[i][j] = diag;
                else
                    m[i][j] = 0.0f;
    }

    Matriz3x3 transposta()
    {
        Matriz3x3 T;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                T.m[i][j] = m[j][i];
        return T;
    }

    Matriz3x3 operator*(float k)
    {
        Matriz3x3 R;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                R.m[i][j] = m[i][j] * k;
        return R;
    }
};

Matriz3x3 operator*(Vetor v1, Vetor v2)
{
    Matriz3x3 M;
    M.m[0][0] = v1.Cord_x * v2.Cord_x;
    M.m[0][1] = v1.Cord_x * v2.Cord_y;
    M.m[0][2] = v1.Cord_x * v2.Cord_z;
    M.m[1][0] = v1.Cord_y * v2.Cord_x;
    M.m[1][1] = v1.Cord_y * v2.Cord_y;
    M.m[1][2] = v1.Cord_y * v2.Cord_z;
    M.m[2][0] = v1.Cord_z * v2.Cord_x;
    M.m[2][1] = v1.Cord_z * v2.Cord_y;
    M.m[2][2] = v1.Cord_z * v2.Cord_z;
    return M;
}

Matriz3x3 operator-(const Matriz3x3 &A, const Matriz3x3 &B)
{
    Matriz3x3 R;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            R.m[i][j] = A.m[i][j] - B.m[i][j];
        }
    }
    return R;
}

Vetor operator*(const Matriz3x3 &M, const Vetor &v)
{
    return Vetor(
        M.m[0][0] * v.Cord_x + M.m[0][1] * v.Cord_y + M.m[0][2] * v.Cord_z,
        M.m[1][0] * v.Cord_x + M.m[1][1] * v.Cord_y + M.m[1][2] * v.Cord_z,
        M.m[2][0] * v.Cord_x + M.m[2][1] * v.Cord_y + M.m[2][2] * v.Cord_z);
}

struct Objeto
{
    Cor K_d, K_e, K_a;
    int m;
    float t_i;
    Vetor Dr;

    virtual bool raioIntercepta(Ponto origem, Ponto canvas) = 0;
    virtual void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) = 0;
};

struct Esfera : public Objeto
{
    Ponto centro;
    float raio;

    Esfera(Ponto c, float r, Cor Kd, Cor Ke, Cor Ka, int M)
    {
        centro = c;
        raio = r;
        K_d = Kd;
        K_e = Ke;
        K_a = Ka;
        m = M;
    }

    bool raioIntercepta(Ponto origem, Ponto canvas) override
    {

        /* direção do raio: origem -> canvas */
        Vetor Dr_local = canvas - origem;

        Vetor w = origem - centro;

        Dr = normalizar(Dr_local);

        /* aplicando o raio na equação da esfera */
        float a = produtoEscalar(Dr, Dr);
        float b = 2 * (produtoEscalar(w, Dr));
        float c = produtoEscalar(w, w) - raio * raio;

        /* bhaskara para verificar se o raio bate na esfera ou não */
        float delta = powf(b, 2) - 4 * a * c;
        if (delta < 0)
            return false;

        float r1 = (-b + sqrt(delta)) / (2 * a);
        float r2 = (-b - sqrt(delta)) / (2 * a);

        float t_valido = -1;

        if (r1 > 0)
        {
            t_valido = r1;
        }

        if (r2 > 0)
        {
            if (t_valido < 0 || r2 < t_valido)
            {
                t_valido = r2;
            }
        }

        if (t_valido > 0)
        {
            t_i = t_valido;
            return true;
        }

        return false;
    }

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override
    {
        /* ponto de interseção */
        Ponto P_I = ray(origem, Dr, t_i);

        /* normal do ponto de interseção */
        Vetor n = normalizar(P_I - centro);

        /* vetor direção da luz */
        Vetor l_vetor = normalizar(P_F - P_I);

        /* vetor direção do observador */
        Vetor v = -Dr;

        float ln = produtoEscalar(l_vetor, n);

        /* vetor reflexão */
        Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

        /* componente difusa */
        Cor I_diff = operadorArroba(K_d, I_F);
        float diff = max(0.0f, ln);
        I_diff.r = I_diff.r * diff;
        I_diff.g = I_diff.g * diff;
        I_diff.b = I_diff.b * diff;

        /* componente especular */
        Cor I_espec = operadorArroba(K_e, I_F);
        float vr = max(0.0f, produtoEscalar(v, r));
        float espec = powf(vr, m);
        I_espec.r = I_espec.r * espec;
        I_espec.g = I_espec.g * espec;
        I_espec.b = I_espec.b * espec;

        /* componente ambiente */
        Cor I_amb = operadorArroba(K_a, I_A);

        finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
        finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
        finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
    }
};

struct Plano : public Objeto
{
    Ponto P_pi;
    Vetor n_bar;

    Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M)
    {
        P_pi = Ppi;
        n_bar = normalizar(nbar);
        K_d = Kd;
        K_e = Ke;
        K_a = Ka;
        m = M;
    }

    bool raioIntercepta(Ponto origem, Ponto canvas) override
    {

        /* direção do raio: origem -> canvas */
        Vetor Dr_local = canvas - origem;

        Dr = normalizar(Dr_local);

        float denom = produtoEscalar(Dr, n_bar);
        if (fabs(denom) > 0)
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

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override
    {
        /* ponto de interseção */
        Ponto P_I = ray(origem, Dr, t_i);

        /* normal do ponto de interseção */
        Vetor n = n_bar;

        /* vetor direção da luz */
        Vetor l_vetor = normalizar(P_F - P_I);

        /* vetor direção do observador */
        Vetor v = -Dr;

        float ln = produtoEscalar(l_vetor, n);

        /* vetor reflexão */
        Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

        /* componente difusa */
        Cor I_diff = operadorArroba(K_d, I_F);
        float diff = max(0.0f, ln);
        I_diff.r = I_diff.r * diff;
        I_diff.g = I_diff.g * diff;
        I_diff.b = I_diff.b * diff;

        /* componente especular */
        Cor I_espec = operadorArroba(K_e, I_F);
        float vr = max(0.0f, produtoEscalar(v, r));
        float espec = powf(vr, m);
        I_espec.r = I_espec.r * espec;
        I_espec.g = I_espec.g * espec;
        I_espec.b = I_espec.b * espec;

        /* componente ambiente */
        Cor I_amb = operadorArroba(K_a, I_A);

        finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
        finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
        finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
    }
};

struct Cilindro : public Objeto
{
    Ponto Centro_base;
    float Raio_base;
    float Altura;
    Vetor Eixo;
    Matriz3x3 Q_Matrix;
    Matriz3x3 M_Matrix;

    Cilindro(Ponto Cb, float Rb, float H, Vetor dr, Cor Kd, Cor Ke, Cor Ka, int m_cor)
    {
        Centro_base = Cb;
        Raio_base = Rb;
        Altura = H;
        Eixo = normalizar(dr);
        K_d = Kd;
        K_e = Ke;
        K_a = Ka;
        m = m_cor;
        Q_Matrix = (Eixo * Eixo) * (1.0f / produtoEscalar(Eixo, Eixo));
        M_Matrix = Matriz3x3(1.0f) - Q_Matrix;
    }

    bool raioIntercepta(Ponto origem, Ponto canvas) override
    {
        Vetor Dr_local = canvas - origem;
        Dr = normalizar(Dr_local);

        Vetor w = origem - Centro_base;

        float a = produtoEscalar(M_Matrix * Dr, M_Matrix * Dr);
        float b = 2.0f * produtoEscalar(M_Matrix * Dr, M_Matrix * w);
        float c = produtoEscalar(M_Matrix * w, M_Matrix * w) - powf(Raio_base, 2);

        float delta = powf(b, 2) - 4 * a * c;
        if (delta < 0)
            return false;

        float r1 = (-b + sqrt(delta)) / (2 * a);
        float r2 = (-b - sqrt(delta)) / (2 * a);

        float t_valido = -1;

        if (r1 > 0)
        {
            Ponto P_I = ray(origem, Dr, r1);
            Vetor v_PI = P_I - Centro_base;
            float altura_Pi = produtoEscalar(Eixo, v_PI);
            if (altura_Pi >= 0 && altura_Pi <= Altura)
            {
                t_valido = r1;
            }
        }

        if (r2 > 0)
        {
            Ponto P_I = ray(origem, Dr, r2);
            Vetor v_PI = P_I - Centro_base;
            float altura_Pi = produtoEscalar(Eixo, v_PI);
            if (altura_Pi >= 0 && altura_Pi <= Altura)
            {
                if (t_valido < 0 || r2 < t_valido)
                {
                    t_valido = r2;
                }
            }
        }

        if (t_valido > 0)
        {
            t_i = t_valido;
            return true;
        }

        return false;
    }

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override
    {
        /* ponto de interseção */
        Ponto P_I = ray(origem, Dr, t_i);

        /* normal do ponto de interseção */
        Vetor n = normalizar(M_Matrix * (P_I - Centro_base));

        /* vetor direção da luz */
        Vetor l_vetor = normalizar(P_F - P_I);

        /* vetor direção do observador */
        Vetor v = -Dr;

        float ln = produtoEscalar(l_vetor, n);

        /* vetor reflexão */
        Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

        /* componente difusa */
        Cor I_diff = operadorArroba(K_d, I_F);
        float diff = max(0.0f, ln);
        I_diff.r = I_diff.r * diff;
        I_diff.g = I_diff.g * diff;
        I_diff.b = I_diff.b * diff;

        /* componente especular */
        Cor I_espec = operadorArroba(K_e, I_F);
        float vr = max(0.0f, produtoEscalar(v, r));
        float espec = powf(vr, m);
        I_espec.r = I_espec.r * espec;
        I_espec.g = I_espec.g * espec;
        I_espec.b = I_espec.b * espec;

        /* componente ambiente */
        Cor I_amb = operadorArroba(K_a, I_A);

        finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
        finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
        finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
    }
};

struct Cone : public Objeto
{
    Ponto Centro_base;
    Ponto Vertice_topo;
    float Raio_base;
    float Altura;
    Vetor Eixo;


    Cone(Ponto Cb, float Rb, float H, Vetor eixo, Cor Kd, Cor Ke, Cor Ka, int M)
    {
        Centro_base = Cb;
        Raio_base = Rb;
        Altura = H;
        Eixo = normalizar(eixo);
        K_d = Kd;
        K_e = Ke;
        K_a = Ka;
        m = M;
        Vertice_topo = ray(Centro_base, Eixo, Altura);
    }

    bool raioIntercepta(Ponto origem, Ponto canvas) override
    {
        Vetor Dr_local = canvas - origem;
        Dr = normalizar(Dr_local);

        Vetor v = Vertice_topo - origem;

        float theta = atan2(Raio_base,Altura);

        float a = powf(produtoEscalar(Dr,Eixo),2.0) - produtoEscalar(Dr, Dr) * powf(cos(theta),2);

        float b = 2 * ( produtoEscalar(Dr, v) * powf(cos(theta),2) - produtoEscalar(Eixo, v) * produtoEscalar(Eixo, Dr) ) ;

        float c = powf(produtoEscalar(Eixo, v),2) - produtoEscalar(v,v) * powf(cos(theta),2);

        float delta = powf(b, 2) - 4 * a * c;
        if (delta < 0)
            return false;

        float r1 = (-b + sqrt(delta)) / (2 * a);
        float r2 = (-b - sqrt(delta)) / (2 * a);

        float t_valido = -1;

        if (r1 > 0)
        {
            Ponto P_I = ray(origem, Dr, r1);
            Vetor CbP = P_I - Centro_base;
            float altura = produtoEscalar(CbP, Eixo);
            if (altura >= 0 && altura <= Altura)
            {
                t_valido = r1;
            }
        }

        if (r2 > 0)
        {
            Ponto P_I = ray(origem, Dr, r2);
            Vetor CbP = P_I - Centro_base;
            float altura = produtoEscalar(CbP, Eixo);
            if (altura >= 0 && altura <= Altura)
            {
                if (t_valido < 0 || r2 < t_valido)
                {
                    t_valido = r2;
                }
            }
        }

        if (t_valido > 0)
        {
            t_i = t_valido;
            return true;
        }

        return false;
    }

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override
    {
        /* ponto de interseção */
        Ponto P_I = ray(origem, Dr, t_i);

        /* normal do ponto de interseção */
        Vetor n = -normalizar(P_I - Vertice_topo);

        /* vetor direção da luz */
        Vetor l_vetor = normalizar(P_F - P_I);

        /* vetor direção do observador */
        Vetor v = -Dr;

        float ln = produtoEscalar(l_vetor, n);

        /* vetor reflexão */
        Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

        /* componente difusa */
        Cor I_diff = operadorArroba(K_d, I_F);
        float diff = max(0.0f, ln);
        I_diff.r = I_diff.r * diff;
        I_diff.g = I_diff.g * diff;
        I_diff.b = I_diff.b * diff;

        /* componente especular */
        Cor I_espec = operadorArroba(K_e, I_F);
        float vr = max(0.0f, produtoEscalar(v, r));
        float espec = powf(vr, m);
        I_espec.r = I_espec.r * espec;
        I_espec.g = I_espec.g * espec;
        I_espec.b = I_espec.b * espec;

        /* componente ambiente */
        Cor I_amb = operadorArroba(K_a, I_A);

        finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
        finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
        finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
    }
};

/* ############################################################## FUNÇÕES ############################################################## */

bool TemSombra(Ponto P_I, Ponto P_F, Objeto *objeto_atual, vector<Objeto *> &objetos)
{
    Vetor L = P_F - P_I;
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

/* ############################################################## MAIN ############################################################## */

int main()
{
    /* origem do Observador */
    Ponto origem = Ponto(0.0f, 0.0f, 0.0f);

    /* janela Real */
    Janela janela = Janela(0.6f, 0.6f, 0.3f);

    /* esfera */
    Esfera esfera = Esfera(Ponto(0.0f, 0.0f, -1.0f), 0.4f, Cor(0.7f, 0.2f, 0.2f), Cor(0.7f, 0.2f, 0.2f), Cor(0.7f, 0.2f, 0.2f), 10);

    /* plano do chão */
    Plano plano_chao = Plano(Ponto(0.0f, -esfera.raio, 0.0f), Vetor(0.0f, 1.0f, 0.0f), Cor(0.2f, 0.7f, 0.2f), Cor(0.0f, 0.0f, 0.0f), Cor(0.2f, 0.7f, 0.2f), 1);

    /* plano do fundo */
    Plano plano_fundo = Plano(Ponto(0.0f, 0.0f, -10.0f), Vetor(0.0f, 0.0f, 1.0f), Cor(0.3f, 0.3f, 0.7f), Cor(0.0f, 0.0f, 0.0f), Cor(0.3f, 0.3f, 0.7f), 1);

    /* direção comum do cilindro e do cone */
    Vetor dir_comum = Vetor(-1.0f / sqrtf(3.0f), 1.0f / sqrtf(3.0f), -1.0f / sqrtf(3.0f));

    /* cilindro */
    Cilindro cilindro = Cilindro(esfera.centro, esfera.raio / 3.0f, 3.0f * esfera.raio, dir_comum, Cor(0.2f, 0.3f, 0.8f), Cor(0.2f, 0.3f, 0.8f), Cor(0.2f, 0.3f, 0.8f), 1);

    /* topo do cilindro */
    Ponto centro_base_cone = ray(cilindro.Centro_base, cilindro.Eixo, cilindro.Altura);

    /* cone */
    Cone cone = Cone(centro_base_cone, esfera.raio * 1.5f, (esfera.raio * 1.5f)/3.0, cilindro.Eixo, Cor(0.8f, 0.3f, 0.2f), Cor(0.8f, 0.3f, 0.2f), Cor(0.8f, 0.3f, 0.2f), 1);

    vector<Objeto *> objetos = {&esfera, &plano_chao, &plano_fundo, &cilindro, &cone};

    /* Luz */
    Cor I_F = Cor(0.7f, 0.7f, 0.7f);
    Ponto P_F = Ponto(0.0f, 0.6f, -0.3f);
    Cor I_A = Cor(0.3f, 0.3f, 0.3f);

    /* canvas pixels: size_t pois não há valores negativos ( e tirar o warning ) */
    size_t nCol = 500;
    size_t nLin = 500;

    /* tamanho dos pixels */
    float Dx = janela.w / float(nCol);
    float Dy = janela.h / float(nLin);

    /* matriz 2d: imagem */
    vector<vector<Cor>> imagem(nLin, vector<Cor>(nCol));

    for (size_t l = 0; l < nLin; l++)
    {
        for (size_t c = 0; c < nCol; c++)
        {
            float x = -janela.w / 2. + Dx / 2 + float(c) * Dx;
            float y = janela.h / 2. - Dy / 2 - float(l) * Dy;

            Cor finalColor;
            float t_closest = -1.0f; /* valor invalido para ser alterado depois */

            Ponto canvas = Ponto(x, y, -janela.d);

            for (Objeto *objeto : objetos)
            {
                if (objeto->raioIntercepta(origem, canvas))
                {
                    if (objeto->t_i > 0 && (t_closest < 0 || objeto->t_i < t_closest))
                    {
                        t_closest = objeto->t_i;

                        Ponto P_I = ray(origem, objeto->Dr, objeto->t_i);

                        if (TemSombra(P_I, P_F, objeto, objetos))
                        {
                            finalColor = operadorArroba(objeto->K_a, I_A);
                        }
                        else
                        {
                            objeto->renderiza(finalColor, origem, P_F, I_F, I_A);
                        }
                    }
                }
            }

            imagem[l][c] = finalColor;
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
            arquivo << imagem[l][c].r * 255 << " " << imagem[l][c].g * 255 << " " << imagem[l][c].b * 255 << " ";
        }

        arquivo << "\n";
    }

    arquivo.close();

    cout << "Imagem gerada em 'imagem_esfera_iluminada.ppm'" << endl;

    return 0;
}