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

bool Triangulo::raioIntercepta(Ponto origem, Ponto canvas)
{
    Vetor Dr_local = canvas - origem;

    Dr = normalizar(Dr_local);

    Vetor v0 = p1 - p0;
    Vetor v1 = p2 - p0;

    Vetor n = produtoVetorial(v0, v1);

    float denom = produtoEscalar(Dr, n);

    if (fabs(denom) < 1e-6)
        return false;

    Vetor w = p0 - origem;
    float t = produtoEscalar(w, n) / denom;

    if (t <= 0)
        return false;

    Ponto P = ray(origem, Dr, t);

    Vetor v2 = P - p0;

    float d00 = produtoEscalar(v0, v0);
    float d01 = produtoEscalar(v0, v1);
    float d11 = produtoEscalar(v1, v1);
    float d20 = produtoEscalar(v2, v0);
    float d21 = produtoEscalar(v2, v1);

    float denom_b = d00 * d11 - d01 * d01;

    float u = (d11 * d20 - d01 * d21) / denom_b;
    float v = (d00 * d21 - d01 * d20) / denom_b;

    if (u < 0 || v < 0 || (u + v) > 1)
        return false;

    t_i = t;
    return true;
}

void Triangulo::renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A)
{
    Ponto P_I = ray(origem, Dr, t_i);

    Vetor v0 = p1 - p0;
    Vetor v1 = p2 - p0;

    Vetor n = normalizar(produtoVetorial(v0, v1));

    Vetor l_vetor = normalizar(P_F - P_I);

    Vetor v = -Dr;

    float ln = produtoEscalar(l_vetor, n);

    Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

    Cor I_diff = operadorArroba(K_d, I_F);
    float diff = max(0.0f, ln);
    I_diff.r = I_diff.r * diff;
    I_diff.g = I_diff.g * diff;
    I_diff.b = I_diff.b * diff;

    Cor I_espec = operadorArroba(K_e, I_F);
    float vr = max(0.0f, produtoEscalar(v, r));
    float espec = powf(vr, m);
    I_espec.r = I_espec.r * espec;
    I_espec.g = I_espec.g * espec;
    I_espec.b = I_espec.b * espec;

    Cor I_amb = operadorArroba(K_a, I_A);

    finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
    finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
    finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
}

void Triangulo::transforma(const Matriz4x4 &M)
{
    p0 = M * p0;
    p1 = M * p1;
    p2 = M * p2;

    atualizarNormal();
}