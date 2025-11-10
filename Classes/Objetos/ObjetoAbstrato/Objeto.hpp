#ifndef OBJETO_HPP
#define OBJETO_HPP

#include "../Utils/Janela/Janela.hpp"
#include "../Utils/Ponto/Ponto.hpp"
#include "../Utils/Vetor/Vetor.hpp"

struct Objeto
{
    Cor K_d, K_e, K_a;
    int m;
    float t_i;
    Vetor Dr;

    virtual bool raioIntercepta(Ponto origem, Ponto canvas) = 0;
    virtual void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) = 0;
};

#endif