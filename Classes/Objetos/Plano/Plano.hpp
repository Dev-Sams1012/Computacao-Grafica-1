#ifndef PLANO_HPP
#define PLANO_HPP

#include "../ObjetoAbstrato/Objeto.hpp"

struct Plano : public Objeto
{
    Ponto P_pi;
    Vetor n_bar;

    Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M);

    bool raioIntercepta(Ponto origem, Ponto canvas) override;

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override;
};

#endif