#include "Objeto.hpp"

void Objeto::renderiza(Cor &finalColor, const HitInfo &hit, const Luz &luz) const
{
    const Ponto& P_I = hit.ponto;

    Vetor n = hit.normal;

    Vetor v = -hit.dr;

    Vetor l_vetor = luz.direcaoNoPonto(P_I);

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

bool Objeto::temSombra(const HitInfo &hit, const Luz &luz, const vector<Objeto *> &objetos) const
{
    Vetor L_dir = luz.direcaoNoPonto(hit.ponto);
    float distanciaAteLuz = luz.distanciaAteLuz(hit.ponto);

    Ponto origemSombra = ray(hit.ponto, L_dir, epsilon);

    for (Objeto *obj : objetos)
    {
        if (hit.objetoRaiz->pertenceA(obj))
            continue;

        HitInfo sombraHit;
        if (obj->raioIntercepta(origemSombra, L_dir, sombraHit))
        {
            if (sombraHit.t > epsilon && sombraHit.t < distanciaAteLuz)
                return true;
        }
    }

    return false;
}

void Objeto::imprimeInformacoes()
{
    cout << "O objeto interceptado tem a forma: ";
    cout << this->getNomeObj() + "\n";
}