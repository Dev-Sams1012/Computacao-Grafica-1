#include "LuzDirecional.hpp"

LuzDirecional::LuzDirecional(const Vetor &d, const Cor &IF) : Luz(IF)
{
    direcao = normalizar(d);
}

Vetor LuzDirecional::direcaoNoPonto(const Ponto &P) const
{
    return -direcao;
}

float LuzDirecional::distanciaAteLuz(const Ponto &P) const
{
    return INFINITY;
}