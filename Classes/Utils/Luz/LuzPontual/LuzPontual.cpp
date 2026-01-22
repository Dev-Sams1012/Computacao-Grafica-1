#include "LuzPontual.hpp"

Vetor LuzPontual::direcaoNoPonto(const Ponto &P) const
{
    return normalizar(PF - P);
}

float LuzPontual::distanciaAteLuz(const Ponto &P) const
{
    return (PF - P).norma();
}