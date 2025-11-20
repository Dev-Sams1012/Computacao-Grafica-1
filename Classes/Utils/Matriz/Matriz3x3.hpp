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

Matriz3x3 operator*(const Matriz3x3 &A, const Matriz3x3 &B);
Matriz3x3 operator-(const Matriz3x3 &A, const Matriz3x3 &B);
Matriz3x3 operator+(const Matriz3x3 &A, const Matriz3x3 &B);

Matriz3x3 operator*(const Vetor &v1, const Vetor &v2);

Matriz3x3 operator*(const Matriz3x3 &M, float k);

Vetor operator*(const Matriz3x3 &M, const Vetor &v);

#endif