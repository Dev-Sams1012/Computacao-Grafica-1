#include "Cilindro.hpp"

Cilindro::Cilindro(Ponto Cb, float Rb, float H, Vetor dr, bool TemBaseInf, bool TemBaseSup, Cor Kd, Cor Ke, Cor Ka, int m_cor) : Objeto(Kd, Ke, Ka, m_cor)
{
    Centro_base = Cb;
    Raio_base = Rb;
    Raio_interno = 0.0f;
    Altura = H;
    Eixo = normalizar(dr);
    temBaseInferior = TemBaseInf;
    temBaseSuperior = TemBaseSup;
    temBaseInterna = false;

    Q_Matrix = (Eixo * Eixo) * (1.0f / produtoEscalar(Eixo, Eixo));
    M_Matrix = Matriz3x3(1.0f) - Q_Matrix;
}

Cilindro::Cilindro(Ponto Cb, float Rb, float Ri, float H, Vetor dr, bool TemBaseInf, bool TemBaseSup, bool TemBaseInt, Cor Kd, Cor Ke, Cor Ka, int m_cor) : Objeto(Kd, Ke, Ka, m_cor)
{
    Centro_base = Cb;
    Raio_base = Rb;
    Raio_interno = Ri;
    Altura = H;
    Eixo = normalizar(dr);
    temBaseInferior = TemBaseInf;
    temBaseSuperior = TemBaseSup;
    temBaseInterna = TemBaseInt;

    Q_Matrix = (Eixo * Eixo) * (1.0f / produtoEscalar(Eixo, Eixo));
    M_Matrix = Matriz3x3(1.0f) - Q_Matrix;
}

bool Cilindro::raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit)
{
    Vetor w = origem - Centro_base;

    float a = produtoEscalar(M_Matrix * Dr, M_Matrix * Dr);
    float b = 2.0f * produtoEscalar(M_Matrix * Dr, M_Matrix * w);

    float c_ext = produtoEscalar(M_Matrix * w, M_Matrix * w) - powf(Raio_base, 2);
    float delta_ext = powf(b, 2) - 4 * a * c_ext;

    float t_valido = -1;
    Vetor normal_temp;

    if (delta_ext >= 0)
    {
        float r1 = (-b + sqrt(delta_ext)) / (2 * a);
        float r2 = (-b - sqrt(delta_ext)) / (2 * a);

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
    }

    if (temBaseInterna && Raio_interno > epsilon)
    {
        float c_int = produtoEscalar(M_Matrix * w, M_Matrix * w) - powf(Raio_interno, 2);
        float delta_int = powf(b, 2) - 4 * a * c_int;

        if (delta_int >= 0)
        {
            float r3 = (-b + sqrt(delta_int)) / (2 * a);
            float r4 = (-b - sqrt(delta_int)) / (2 * a);

            if (r3 > epsilon)
            {
                Ponto P_I = ray(origem, Dr, r3);
                float altura_Pi = produtoEscalar(Eixo, P_I - Centro_base);
                if (altura_Pi >= 0 && altura_Pi <= Altura)
                {
                    if (t_valido < 0 || r3 < t_valido)
                    {
                        t_valido = r3;
                        normal_temp = -normalEm(P_I);
                    }
                }
            }

            if (r4 > epsilon)
            {
                Ponto P_I = ray(origem, Dr, r4);
                float altura_Pi = produtoEscalar(Eixo, P_I - Centro_base);
                if (altura_Pi >= 0 && altura_Pi <= Altura)
                {
                    if (t_valido < 0 || r4 < t_valido)
                    {
                        t_valido = r4;
                        normal_temp = -normalEm(P_I);
                    }
                }
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
            float distSq = produtoEscalar(d, d);
            if (distSq <= Raio_base * Raio_base && distSq >= Raio_interno * Raio_interno)
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
            float distSq = produtoEscalar(d, d);
            if (distSq <= Raio_base * Raio_base && distSq >= Raio_interno * Raio_interno)
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