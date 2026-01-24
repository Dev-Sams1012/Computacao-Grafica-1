#include "Cilindro.hpp"

Cilindro::Cilindro(Ponto Cb, float Rb, float H, Vetor dr, bool TemBaseInf, bool TemBaseSup, Cor Kd, Cor Ke, Cor Ka, int m_cor) : Objeto(Kd, Ke, Ka, m_cor)
{
    Centro_base = Cb;
    Raio_base = Rb;
    Altura = H;
    Eixo = normalizar(dr);
    temBaseInferior = TemBaseInf;
    temBaseSuperior = TemBaseSup;
    Q_Matrix = (Eixo * Eixo) * (1.0f / produtoEscalar(Eixo, Eixo));
    M_Matrix = Matriz3x3(1.0f) - Q_Matrix;
}

bool Cilindro::raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit)
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
    Vetor normal_temp;

    if (r1 > epsilon)
    {
        Ponto P_I = ray(origem, Dr, r1);
        Vetor v_PI = P_I - Centro_base;
        float altura_Pi = produtoEscalar(Eixo, v_PI);
        if (altura_Pi >= 0 && altura_Pi <= Altura)
        {
            t_valido = r1;
        }
    }

    if (r2 > epsilon)
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
        if (t_base > epsilon)
        {
            Ponto P_base = ray(origem, Dr, t_base);
            Vetor d = P_base - Centro_base;
            if (produtoEscalar(d, d) <= Raio_base * Raio_base)
            {
                if (t_valido < 0 || t_base < t_valido)
                {
                    t_valido = t_base;
                    normal_temp = -Eixo;
                }
            }
        }
    }
    if (temBaseSuperior)
    {
        Ponto topo = ray(Centro_base, Eixo, Altura);
        float t_topo = produtoEscalar(Eixo, topo - origem) / produtoEscalar(Eixo, Dr);
        if (t_topo > epsilon)
        {
            Ponto P_topo = ray(origem, Dr, t_topo);
            Vetor d = P_topo - topo;
            if (produtoEscalar(d, d) <= Raio_base * Raio_base)
            {
                if (t_valido < 0 || t_topo < t_valido)
                {
                    t_valido = t_topo;
                    normal_temp = Eixo;
                }
            }
        }
    }

    if (t_valido > epsilon && t_valido < hit.t)
    {
        hit.t = t_valido;
        hit.objeto = this;
        hit.objetoRaiz = this;
        hit.ponto = ray(origem, Dr, t_valido);
        if (normal_temp.norma() < 0.5f)
        {
            hit.normal = normalizar(normalEm(hit.ponto));
        }
        else
        {
            hit.normal = normalizar(normal_temp);
        }
        return true;
    }

    return false;
}

void Cilindro::transforma(const Matriz4x4 &M)
{
    Centro_base = M * Centro_base;
    Eixo = normalizar(M * Eixo);

    Q_Matrix = (Eixo * Eixo) * (1.0f / produtoEscalar(Eixo, Eixo));
    M_Matrix = Matriz3x3(1.0f) - Q_Matrix;
}

Vetor Cilindro::normalEm(const Ponto &P) const
{
    return normalizar(M_Matrix * (P - Centro_base));
}