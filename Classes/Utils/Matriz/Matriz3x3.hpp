#ifndef MATRIZ3X3_HPP
#define MATRIZ3X3_HPP

using namespace std;

#include "../Vetor/Vetor.hpp"

struct Matriz3x3
{
    float m[3][3];

    Matriz3x3(float diag = 0.0f);

    Matriz3x3 transposta();
};

Matriz3x3 operator*(Vetor v1, Vetor v2);

Matriz3x3 operator-(Matriz3x3 A, Matriz3x3 B);

Matriz3x3 operator+(Matriz3x3 A, Matriz3x3 B);

Matriz3x3 operator*(Matriz3x3 M, float k);

Vetor operator*(Matriz3x3 M, Vetor v);

#endif