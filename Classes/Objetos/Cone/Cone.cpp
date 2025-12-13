#include "Cone.hpp"

Cone::Cone(Ponto Cb, float Rb, float H, Vetor dr, bool temBase, Cor Kd, Cor Ke, Cor Ka, int M)
{
    Centro_base = Cb;
    Raio_base = Rb;
    Altura = H;
    Eixo = normalizar(dr);
    TemBase = temBase;
    K_d = Kd;
    K_e = Ke;
    K_a = Ka;
    m = M;
    Vertice_topo = ray(Centro_base, Eixo, Altura);
    Q_Matrix = (Eixo * Eixo) * (1.0f / produtoEscalar(Eixo, Eixo));
    M_Matrix = Matriz3x3(1.0f) - Q_Matrix;
}

bool Cone::raioIntercepta(const Ponto &origem, const Vetor &Dr)
{
    Vetor w = origem - Centro_base;

    Vetor M_dr = M_Matrix * Dr;
    Vetor Q_dr = Q_Matrix * Dr;
    Vetor M_w = M_Matrix * w;
    Vetor Q_w = Q_Matrix * w;

    Vetor h_dc = Vertice_topo - Centro_base;

    float a = powf(Altura, 2) * produtoEscalar(M_dr, M_dr) - powf(Raio_base, 2) * produtoEscalar(Q_dr, Q_dr);

    float b = 2.0f * (powf(Altura, 2) * produtoEscalar(M_dr, M_w) + powf(Raio_base, 2) * produtoEscalar(Q_dr, h_dc - Q_w));

    float c = powf(Altura, 2) * produtoEscalar(M_w, M_w) - powf(Raio_base, 2) * produtoEscalar(Q_w - h_dc, Q_w - h_dc);

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

    if (TemBase)
    {
        float t_base = produtoEscalar(Eixo, Centro_base - origem) / produtoEscalar(Eixo, Dr);
        if (t_base > 0)
        {
            Ponto P_base = ray(origem, Dr, t_base);
            Vetor d = P_base - Centro_base;
            if (produtoEscalar(d, d) <= Raio_base * Raio_base)
            {
                if (t_valido < 0 || t_base < t_valido)
                    t_valido = t_base;
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

void Cone::transforma(const Matriz4x4 &M)
{
    Centro_base = M * Centro_base;
    Eixo = normalizar(M * Eixo);
}

Vetor Cone::normalEm(const Ponto &P) const
{
    return -normalizar(P - Vertice_topo);
}