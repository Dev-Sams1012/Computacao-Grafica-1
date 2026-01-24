#ifndef HITINFO_HPP
#define HITINFO_HPP

#include "../Ponto/Ponto.hpp"
#include "../Vetor/Vetor.hpp"

#include <math.h>

struct Objeto;

struct HitInfo
{
    float t = INFINITY;
    Ponto ponto;
    Vetor normal;
    Vetor dr;
    Ponto origem;
    Objeto* objeto = nullptr;
    Objeto* objetoRaiz = nullptr;
};

#endif
