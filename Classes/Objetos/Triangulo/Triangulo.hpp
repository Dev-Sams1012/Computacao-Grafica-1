#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "../ObjetoAbstrato/Objeto.hpp"

struct Triangulo : Objeto
{
    Ponto p0;
    Ponto p1;
    Ponto p2;
 
    Triangulo(Ponto p1, Ponto p2, Ponto p0, Cor Kd, Cor Ke, Cor Ka, int M);

    bool raioIntercepta(Ponto origem, Ponto canvas) override;

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override;
};

#endif