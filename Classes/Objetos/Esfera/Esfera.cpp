#include "Esfera.hpp"

Esfera::Esfera(Ponto c, float r, Cor Kd, Cor Ke, Cor Ka, int M)
{
    centro = c;
    raio = r;
    K_d = Kd;
    K_e = Ke;
    K_a = Ka;
    m = M;
}

bool Esfera::raioIntercepta(const Ponto &origem, const Vetor &Dr)
{
    Vetor w = origem - centro;

    float a = produtoEscalar(Dr, Dr);
    float b = 2 * (produtoEscalar(w, Dr));
    float c = produtoEscalar(w, w) - raio * raio;

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

Vetor Esfera::normalEm(const Ponto &P) const
{
    return normalizar(P - centro);
}

void Esfera::transforma(const Matriz4x4 &M)
{
    centro = M * centro;
}