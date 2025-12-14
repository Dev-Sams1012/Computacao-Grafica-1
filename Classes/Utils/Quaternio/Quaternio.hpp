#include "../Vetor/Vetor.hpp"
#include "../Matriz/Matriz4x4.hpp"

#ifndef QUATERNIO_HPP
#define QUATERNIO_HPP

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
};

#endif