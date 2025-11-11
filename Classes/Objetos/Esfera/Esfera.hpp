#ifndef ESFERA_HPP
#define ESFERA_HPP

#include <cmath>
#include <algorithm>

#include "../ObjetoAbstrato/Objeto.hpp"

struct Esfera : public Objeto
{
    Ponto centro;
    float raio;

    Esfera(Ponto c, float r, Cor Kd, Cor Ke, Cor Ka, int M);

    bool raioIntercepta(Ponto origem, Ponto canvas) override;

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override;
};

#endif