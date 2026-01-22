#include "LuzDirecional.hpp"

Vetor LuzDirecional::direcaoNoPonto(const Ponto &P) const
{
    return -direcao;
}

float LuzDirecional::distanciaAteLuz(const Ponto &P) const
{
    return INFINITY;
}