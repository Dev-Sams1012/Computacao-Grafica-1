#include "LuzPontual.hpp"

LuzPontual::LuzPontual(const Ponto &PF, const Cor &IF) : Luz(IF)
{
    this->PF = PF;
}

Vetor LuzPontual::direcaoNoPonto(const Ponto &P) const
{
    return normalizar(PF - P);
}

float LuzPontual::distanciaAteLuz(const Ponto &P) const
{
    return (PF - P).norma();
}