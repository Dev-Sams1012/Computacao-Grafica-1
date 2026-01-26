#include "../Vetor/Vetor.hpp"

#ifndef QUATERNIO_HPP
#define QUATERNIO_HPP

struct Matriz4x4; 

using namespace std;

struct Quaternio
{
    float w;
    Vetor ijk;

    Quaternio(float w = 1, Vetor v = Vetor(0, 0, 0));

    Quaternio conjugado() const;

    float norma() const;

    Quaternio normalizado() const;

    Quaternio operator*(const Quaternio &q) const;

    Matriz4x4 toRotationMatrix() const;

    static Quaternio rotacaoEixo(Vetor eixo, float ang);
};

#endif