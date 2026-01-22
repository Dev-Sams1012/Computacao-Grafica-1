#ifndef LUZ_HPP
#define LUZ_HPP

#include "../Janela/Janela.hpp"
#include "../Ponto/Ponto.hpp"
#include "../Vetor/Vetor.hpp"

#include <cmath>

struct Luz
{
    Cor IF;

    Luz(const Cor &IF) : IF(IF) {};

    virtual Vetor direcaoNoPonto(const Ponto &P) const = 0;

    virtual float distanciaAteLuz(const Ponto &P) const = 0;

    virtual bool iluminaPonto(const Ponto &P) const { return true; }
};

#endif