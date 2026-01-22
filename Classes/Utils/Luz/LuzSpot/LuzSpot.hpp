#ifndef LUZSPOT_HPP
#define LUZSPOT_HPP

#include "../Luz.hpp"

struct LuzSpot : Luz
{
    Ponto PF;
    Vetor direcao;
    float angulo;

    LuzSpot(const Ponto &PF, const Vetor &d, float ang, const Cor &IF);

    Vetor direcaoNoPonto(const Ponto &P) const override;

    float distanciaAteLuz(const Ponto &P) const override;
    
    bool iluminaPonto(const Ponto &P) const override;
};

#endif