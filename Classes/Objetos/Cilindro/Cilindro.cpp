#include "Cilindro.hpp"

Cilindro::Cilindro(Ponto Cb, float Rb, float H, Vetor dr, bool TemBaseInf, bool TemBaseSup, Cor Kd, Cor Ke, Cor Ka, int m_cor)
{
    Centro_base = Cb;
    Raio_base = Rb;
    Altura = H;
    Eixo = normalizar(dr);
    K_d = Kd;
    K_e = Ke;
    K_a = Ka;
    m = m_cor;
    temBaseInferior = TemBaseInf;
    temBaseSuperior = TemBaseSup;
    Q_Matrix = (Eixo * Eixo) * (1.0f / produtoEscalar(Eixo, Eixo));
    M_Matrix = Matriz3x3(1.0f) - Q_Matrix;
}

bool Cilindro::raioIntercepta(const Ponto &origem, const Vetor &Dr)
{
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

    if (temBaseInferior)
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
    if (temBaseSuperior)
    {
        Ponto topo = ray(Centro_base, Eixo, Altura);
        float t_topo = produtoEscalar(Eixo, topo - origem) / produtoEscalar(Eixo, Dr);
        if (t_topo > 0)
        {
            Ponto P_topo = ray(origem, Dr, t_topo);
            Vetor d = P_topo - topo;
            if (produtoEscalar(d, d) <= Raio_base * Raio_base)
            {
                if (t_valido < 0 || t_topo < t_valido)
                    t_valido = t_topo;
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

void Cilindro::transforma(const Matriz4x4 &M)
{
    Centro_base = M * Centro_base;
    Eixo = normalizar(M * Eixo);
}

Vetor Cilindro::normalEm(const Ponto &P) const{
    return normalizar(M_Matrix * (P - Centro_base));
}