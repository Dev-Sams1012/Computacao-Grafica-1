#ifndef VETOR_HPP
#define VETOR_HPP

using namespace std;

#include "../Ponto/Ponto.hpp"

struct Vetor
{
    float Cord_x, Cord_y, Cord_z, Cord_w = 0.0f;

    Vetor(float x = 0, float y = 0, float z = 0);

    float norma();
};

Vetor normalizar(const Vetor &v);

float produtoEscalar(const Vetor &v1, const Vetor &v2);

Vetor produtoVetorial(const Vetor &v1, const Vetor &v2);
Ponto ray(const Ponto &p, const Vetor &v, float t);

Vetor operator-(const Ponto &p2, const Ponto &p1);

Vetor operator-(const Vetor &v1, const Vetor &v2);

Vetor operator-(const Vetor &v);

Vetor operator+(const Vetor &v1, const Vetor &v2);

Vetor operator*(float k, const Vetor &v);

Vetor operator*(const Vetor &v, float k);

Vetor operator/(const Vetor &v, float k);

#endif