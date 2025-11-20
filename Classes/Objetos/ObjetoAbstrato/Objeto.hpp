#ifndef OBJETO_HPP
#define OBJETO_HPP

#include <cmath>
#include <algorithm>
#include <vector>

#include "../../Utils/Janela/Janela.hpp"
#include "../../Utils/Janela/Luz.hpp"
#include "../../Utils/Ponto/Ponto.hpp"
#include "../../Utils/Vetor/Vetor.hpp"
#include "../../Utils/Matriz/Matriz3x3.hpp"

struct Objeto
{
    Cor K_d, K_e, K_a;
    int m;
    float t_i;
    Vetor Dr;

    virtual bool raioIntercepta(Ponto origem, Ponto canvas) = 0;
    virtual void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) = 0;
    virtual bool temTextura() const { return false; }
    virtual Cor texturaEm(const Ponto &p) const { return K_d; }
    bool temSombra(Ponto P_I, Luz luz, Objeto *objeto_atual, vector<Objeto *> objetos);
};

#endif