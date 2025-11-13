#ifndef VETOR_HPP
#define VETOR_HPP

using namespace std;

#include "../Ponto/Ponto.hpp"

struct Vetor
{
    float Cord_x, Cord_y, Cord_z;

    Vetor(float x = 0, float y = 0, float z = 0);

    float norma();
};

Vetor normalizar(Vetor v);

float produtoEscalar(Vetor v1, Vetor v2);

Vetor produtoVetorial(Vetor v1, Vetor v2);

Ponto ray(Ponto p, Vetor v, float t);

Vetor operator-(Ponto p2, Ponto p1);

Vetor operator-(Vetor v1, Vetor v2);

Vetor operator-(Vetor v);

Vetor operator+(Vetor v1, Vetor v2);

Vetor operator*(float k, Vetor v);

Vetor operator*(Vetor v, float k);

Vetor operator/(Vetor v, float k);

#endif