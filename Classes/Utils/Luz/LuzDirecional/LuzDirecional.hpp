#ifndef LUZDIRECIONAL_HPP
#define LUZDIRECIONAL_HPP

#include "Luz.hpp"

struct LuzDirecional : Luz
{
    Vetor direcao;

    LuzDirecional(const Vetor &d, const Cor &IF) : Luz(IF), direcao(normalizar(d)) {};

    Vetor direcaoNoPonto(const Ponto &P) const override;

    float distanciaAteLuz(const Ponto &P) const override;
};

#endif