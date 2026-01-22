#include "LuzSpot.hpp"

LuzSpot::LuzSpot(const Ponto &PF, const Vetor &d, float ang, const Cor &IF) : Luz(IF)
{
    this->PF = PF;
    direcao = normalizar(d);
    angulo = ang;
}

Vetor LuzSpot::direcaoNoPonto(const Ponto &P) const
{
    return normalizar(PF - P);
}

float LuzSpot::distanciaAteLuz(const Ponto &P) const
{
    return (PF - P).norma();
}

bool LuzSpot::iluminaPonto(const Ponto &P) const
{
    Vetor L = normalizar(P - PF);
    float cosAng = produtoEscalar(L, direcao);
    return cosAng >= cos(angulo);
}