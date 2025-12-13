#ifndef OBJETO_HPP
#define OBJETO_HPP

#include <cmath>
#include <algorithm>
#include <vector>

#include "../../Utils/Janela/Janela.hpp"
#include "../../Utils/Luz/Luz.hpp"
#include "../../Utils/Ponto/Ponto.hpp"
#include "../../Utils/Vetor/Vetor.hpp"
#include "../../Utils/Matriz/Matriz3x3.hpp"
#include "../../Utils/Matriz/Matriz4x4.hpp"

struct Objeto
{
    Cor K_d, K_e, K_a;
    int m;
    float t_i;

    virtual bool raioIntercepta(const Ponto &origem, const Vetor &Dr) = 0;
    virtual Vetor normalEm(const Ponto &P) const = 0;

    virtual void renderiza(Cor &finalColor, const Ponto &origem, const Vetor &Dr, const Ponto &P_F, Cor I_F, Cor I_A) const;
    bool temSombra(const Ponto &P_I, const Luz &luz, Objeto *objeto_atual, const vector<Objeto *> &objetos);
    virtual bool pertenceA(const Objeto *obj) const { return this == obj; }

    virtual bool temTextura() const { return false; }
    virtual Cor texturaEm(const Ponto &p) const { return K_d; }

    virtual void transforma(const Matriz4x4 &M) = 0;
};

#endif