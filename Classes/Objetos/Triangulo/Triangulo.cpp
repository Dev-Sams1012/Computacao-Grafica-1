#include "Triangulo.hpp"

Triangulo::Triangulo(Ponto p1, Ponto p2, Ponto p0, Cor Kd, Cor Ke, Cor Ka, int M)
{
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->K_d = Kd;
    this->K_e = Ke;
    this->K_a = Ka;
    this->m = M;

    atualizarNormal();
}

void Triangulo::atualizarNormal()
{
    Vetor v0 = p1 - p0;
    Vetor v1 = p2 - p0;
    normal = normalizar(produtoVetorial(v0, v1));
}

bool Triangulo::raioIntercepta(const Ponto &origem, const Vetor &Dr)
{
    const float EPS = 1e-6f;

    Vetor v0 = p1 - p0;
    Vetor v1 = p2 - p0;

    Vetor n = produtoVetorial(v0, v1);

    float denom = produtoEscalar(Dr, n);
    if (fabs(denom) < EPS)
        return false;

    float t = produtoEscalar(p0 - origem, n) / denom;
    if (t <= EPS)
        return false;

    Ponto P = ray(origem, Dr, t);

    Vetor v2 = P - p0;

    float d00 = produtoEscalar(v0, v0);
    float d01 = produtoEscalar(v0, v1);
    float d11 = produtoEscalar(v1, v1);
    float d20 = produtoEscalar(v2, v0);
    float d21 = produtoEscalar(v2, v1);

    float denom_b = d00 * d11 - d01 * d01;
    if (fabs(denom_b) < EPS)
        return false;

    float u = (d11 * d20 - d01 * d21) / denom_b;
    float v = (d00 * d21 - d01 * d20) / denom_b;

    if (u < 0.0f || v < 0.0f || (u + v) > 1.0f)
        return false;

    t_i = t;
    return true;
}

void Triangulo::transforma(const Matriz4x4 &M)
{
    p0 = M * p0;
    p1 = M * p1;
    p2 = M * p2;

    atualizarNormal();
}

Vetor Triangulo::normalEm(const Ponto &P) const
{
    return normal;
}