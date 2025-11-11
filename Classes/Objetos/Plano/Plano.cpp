#include "Plano.hpp"

Plano::Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M)
{
    P_pi = Ppi;
    n_bar = normalizar(nbar);
    K_d = Kd;
    K_e = Ke;
    K_a = Ka;
    m = M;
}

bool Plano::raioIntercepta(Ponto origem, Ponto canvas)
{
    Vetor Dr_local = canvas - origem;

    Dr = normalizar(Dr_local);

    float denom = produtoEscalar(Dr, n_bar);
    if (fabs(denom) > 0)
    {
        Vetor w = P_pi - origem;
        float t = produtoEscalar(w, n_bar) / denom;

        if (t > 0)
        {
            t_i = t;
            return true;
        }
    }

    return false;
}

void Plano::renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A)
{
    Ponto P_I = ray(origem, Dr, t_i);

    Vetor n = n_bar;

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