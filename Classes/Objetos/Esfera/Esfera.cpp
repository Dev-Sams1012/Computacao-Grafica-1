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

bool Esfera::raioIntercepta(Ponto origem, Ponto canvas)
{
    Vetor Dr_local = canvas - origem;

    Vetor w = origem - centro;

    Dr = normalizar(Dr_local);

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

void Esfera::renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A)
{
    Ponto P_I = ray(origem, Dr, t_i);

    Vetor n = normalizar(P_I - centro);

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

void Esfera::transforma(const Matriz4x4 &M)
{
    centro = M * centro;
}