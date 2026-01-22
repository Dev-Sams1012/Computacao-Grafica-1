#include "Objeto.hpp"

void Objeto::renderiza(Cor &finalColor, const Ponto &origem, const Vetor &Dr, const Luz &luz) const
{
    Ponto P_I = ray(origem, Dr, t_i);

    Vetor n = normalizar(normalEm(P_I));

    Vetor l_vetor = luz.direcaoNoPonto(P_I);

    Vetor v = -Dr;

    float ln = produtoEscalar(l_vetor, n);

    Vetor r = normalizar((n * (2.0f * ln)) - l_vetor);

    Cor kd = temTextura() ? texturaEm(P_I) : K_d;
    Cor ke = temTextura() ? texturaEm(P_I) : K_e;
    Cor ka = temTextura() ? texturaEm(P_I) : K_a;

    Cor I_F = luz.IF;

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

    finalColor.r = I_diff.r + I_espec.r;
    finalColor.g = I_diff.g + I_espec.g;
    finalColor.b = I_diff.b + I_espec.b;
}

bool Objeto::temSombra(const Ponto &P_I, const Luz &luz, Objeto *objeto_atual, const vector<Objeto *> &objetos)
{
    Vetor L_dir = luz.direcaoNoPonto(P_I);
    float distanciaAteLuz = luz.distanciaAteLuz(P_I);
    
    float epsilon = 0.001f;

    Ponto origemSombra = ray(P_I, L_dir, epsilon);

    for (Objeto *objeto : objetos)
    {
        if (!objeto_atual->pertenceA(objeto))
        {
            if (objeto->raioIntercepta(origemSombra, L_dir))
            {
                if (objeto->t_i > epsilon && objeto->t_i < distanciaAteLuz)
                {
                    return true;
                }
            }
        }
    }

    return false;
}