#include "Objeto.hpp"

void Objeto::renderiza(Cor &finalColor, const Ponto &origem, const Vetor &Dr, const Ponto &P_F, Cor I_F, Cor I_A) const
{
    Ponto P_I = ray(origem, Dr, t_i);

    Vetor n = normalizar(normalEm(P_I));

    Vetor l_vetor = normalizar(P_F - P_I);

    Vetor v = -Dr;

    float ln = produtoEscalar(l_vetor, n);

    Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

    Cor kd = temTextura() ? texturaEm(P_I) : K_d;
    Cor ke = temTextura() ? texturaEm(P_I) : K_e;
    Cor ka = temTextura() ? texturaEm(P_I) : K_a;

    Cor I_diff = operadorArroba(kd, I_F);
    float diff = max(0.0f, ln);
    I_diff.r = I_diff.r * diff;
    I_diff.g = I_diff.g * diff;
    I_diff.b = I_diff.b * diff;

    Cor I_espec = operadorArroba(ke, I_F);
    float vr = max(0.0f, produtoEscalar(v, r));
    float espec = powf(vr, m);
    I_espec.r = I_espec.r * espec;
    I_espec.g = I_espec.g * espec;
    I_espec.b = I_espec.b * espec;

    Cor I_amb = operadorArroba(ka, I_A);

    finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
    finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
    finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
}

bool Objeto::temSombra(const Ponto &P_I, const Luz &luz, Objeto *objeto_atual, const vector<Objeto *> &objetos)
{
    Vetor L = luz.PF - P_I;
    float distancia_Pi_Pf = sqrtf(produtoEscalar(L, L));
    if (distancia_Pi_Pf <= 0.0f)
        return false;

    Vetor L_dir = normalizar(L);
    float epsilon = 0.001f;

    Ponto Ponto_Luz = ray(P_I, L_dir, distancia_Pi_Pf);

    for (Objeto *objeto : objetos)
    {
        if (!objeto_atual->pertenceA(objeto))
        {
            if (objeto->raioIntercepta(P_I, L_dir))
            {
                if (objeto->t_i > epsilon && objeto->t_i < distancia_Pi_Pf)
                {
                    return true;
                }
            }
        }
    }

    return false;
}