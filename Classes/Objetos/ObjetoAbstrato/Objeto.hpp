#ifndef OBJETO_HPP
#define OBJETO_HPP

#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

#include "../../Utils/Janela/Janela.hpp"
#include "../../Utils/Luz/Luz.hpp"
#include "../../Utils/Ponto/Ponto.hpp"
#include "../../Utils/Vetor/Vetor.hpp"
#include "../../Utils/Matriz/Matriz3x3.hpp"
#include "../../Utils/Matriz/Matriz4x4.hpp"
#include "../../Utils/HitInfo/HitInfo.hpp"

#define epsilon 1e-6

using namespace std;

struct Objeto
{
    Cor K_d, K_e, K_a;
    int m;

    Objeto(const Cor &Kd, const Cor &Ke, const Cor &Ka, int m) : K_d(Kd), K_e(Ke), K_a(Ka), m(m) {}

    virtual bool raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit) = 0;

    virtual Vetor normalEm(const Ponto &P) const = 0;

    virtual void renderiza(Cor &finalColor, const HitInfo &hit, const Luz &luz) const;

    bool temSombra(const HitInfo &hit, const Luz &luz, const vector<Objeto *> &objetos) const;

    virtual bool pertenceA(const Objeto *obj) const { return this == obj; }

    virtual bool temTextura() const { return false; }

    virtual Cor texturaEm(const Ponto &p) const { return K_d; }

    virtual void transforma(const Matriz4x4 &M) = 0;

    virtual string getNomeObj() const = 0;

    virtual void imprimeInformacoes();
};

#endif