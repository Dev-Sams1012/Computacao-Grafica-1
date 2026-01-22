#ifndef LUZPONTUAL_HPP
#define LUZPONTUAL_HPP

#include "Luz.hpp"

struct LuzPontual : Luz
{
    Ponto PF;

    LuzPontual(const Ponto &PF, const Cor &IF) : Luz(IF), PF(PF) {};

    Vetor direcaoNoPonto(const Ponto &P) const override;

    float distanciaAteLuz(const Ponto &P) const override;
};

#endif