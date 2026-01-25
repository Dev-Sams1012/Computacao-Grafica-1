#include "Cone.hpp"

Cone::Cone(Ponto Cb, float Rb, float H, Vetor dr, bool temBase, Cor Kd, Cor Ke, Cor Ka, int M) : Objeto(Kd, Ke, Ka, M)
{
    Centro_base = Cb;
    Raio_base = Rb;
    Altura = H;
    Altura_corte = H;
    Eixo = normalizar(dr);
    TemBase = temBase;
    TemTampaSuperior = false;
    Vertice_topo = ray(Centro_base, Eixo, Altura);
    Q_Matrix = (Eixo * Eixo) * (1.0f / produtoEscalar(Eixo, Eixo));
    M_Matrix = Matriz3x3(1.0f) - Q_Matrix;
}

Cone::Cone(Ponto Cb, float Rb, float H, float H_corte, Vetor dr, bool temBase, bool temTampaSup, Cor Kd, Cor Ke, Cor Ka, int M) : Objeto(Kd, Ke, Ka, M)
{
    Centro_base = Cb;
    Raio_base = Rb;
    Altura = H;
    Altura_corte = H_corte;
    Eixo = normalizar(dr);
    TemBase = temBase;
    TemTampaSuperior = temTampaSup;
    Vertice_topo = ray(Centro_base, Eixo, Altura);
    Q_Matrix = (Eixo * Eixo) * (1.0f / produtoEscalar(Eixo, Eixo));
    M_Matrix = Matriz3x3(1.0f) - Q_Matrix;
}

bool Cone::raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit)
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

    if (r1 > epsilon)
    {
        Ponto P_I = ray(origem, Dr, r1);
        Vetor CbP = P_I - Centro_base;
        float altura = produtoEscalar(CbP, Eixo);
        if (altura >= 0 && altura <= Altura_corte)
        {
            t_valido = r1;
        }
    }

    if (r2 > epsilon)
    {
        Ponto P_I = ray(origem, Dr, r2);
        Vetor CbP = P_I - Centro_base;
        float altura = produtoEscalar(CbP, Eixo);
        if (altura >= 0 && altura <= Altura_corte)
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
        if (t_base > epsilon)
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

    if (TemTampaSuperior && Altura_corte < Altura)
    {
        Ponto P_topo_centro = ray(Centro_base, Eixo, Altura_corte);
        float t_s = produtoEscalar(Eixo, P_topo_centro - origem) / produtoEscalar(Eixo, Dr);

        if (t_s > epsilon)
        {
            Ponto P_s = ray(origem, Dr, t_s);
            float Raio_corte = Raio_base * (1.0f - (Altura_corte / Altura));
            if (produtoEscalar(P_s - P_topo_centro, P_s - P_topo_centro) <= powf(Raio_corte, 2))
            {
                if (t_valido < 0 || t_s < t_valido)
                    t_valido = t_s;
            }
        }
    }

    if (t_valido > epsilon && t_valido < hit.t)
    {
        hit.t = t_valido;
        hit.objeto = this;
        hit.objetoRaiz = this;
        hit.ponto = ray(origem, Dr, t_valido);

        Vetor normalCalculada = normalizar(normalEm(hit.ponto));

        if (produtoEscalar(Dr, normalCalculada) > 0)
        {
            hit.normal = -normalCalculada;
        }
        else
        {
            hit.normal = normalCalculada;
        }

        return true;
    }

    return false;
}

void Cone::transforma(const Matriz4x4 &M)
{
    Centro_base = M * Centro_base;
    Eixo = normalizar(M * Eixo);
    Vertice_topo = ray(Centro_base, Eixo, Altura);
}

Vetor Cone::normalEm(const Ponto &P) const
{
    Vetor CP = P - Centro_base;
    float h = produtoEscalar(CP, Eixo);

    if (h < epsilon)
    {
        return -Eixo;
    }

    if (h > Altura_corte - epsilon)
    {
        return Eixo;
    }

    Ponto P_eixo = ray(Centro_base, Eixo, h);
    Vetor radial = normalizar(P - P_eixo);

    float inclinacao = Raio_base / Altura;

    return normalizar(radial + Eixo * inclinacao);
}