#include "Esfera.hpp"

Esfera::Esfera(Ponto c, float r, Cor Kd, Cor Ke, Cor Ka, int M) : Objeto(Kd, Ke, Ka, M)
{
    centro = c;
    raio = r;
}

bool Esfera::raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit)
{
    Vetor w = origem - centro;

    float a = produtoEscalar(Dr, Dr);
    float b = 2.0f * produtoEscalar(w, Dr);
    float c = produtoEscalar(w, w) - raio * raio;

    float delta = b * b - 4 * a * c;
    if (delta < 0)
        return false;

    float sqrt_delta = sqrt(delta);
    float t1 = (-b - sqrt_delta) / (2 * a);
    float t2 = (-b + sqrt_delta) / (2 * a);

    float t = -1.0f;

    if (t1 > epsilon)
        t = t1;
    else if (t2 > epsilon)
        t = t2;
    else
        return false;

    if (t > epsilon && t < hit.t)
    {
        hit.t = t;
        hit.objeto = this;
        hit.objetoRaiz = this;
        hit.ponto = ray(origem, Dr, t);
        hit.normal = normalizar(hit.ponto - centro);
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