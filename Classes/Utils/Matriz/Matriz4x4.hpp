#ifndef MATRIZ4X4_HPP
#define MATRIZ4X4_HPP

#include <cmath>

using namespace std;

#include "../Ponto/Ponto.hpp"
#include "../Vetor/Vetor.hpp"

struct Matriz4x4
{
    float m[4][4];

    Matriz4x4(float diag = 0.0f);

    Matriz4x4 transposta() const;

    static Matriz4x4 translacao(float tx, float ty, float tz);
    static Matriz4x4 escala(float sx, float sy, float sz);
    static Matriz4x4 rotacaoX(float ang);
    static Matriz4x4 rotacaoY(float ang);
    static Matriz4x4 rotacaoZ(float ang);
    static Matriz4x4 cisalhaXY(float ang);
    static Matriz4x4 cisalhaYX(float ang);
    static Matriz4x4 cisalhaXZ(float ang);
    static Matriz4x4 cisalhaZX(float ang);
    static Matriz4x4 cisalhaYZ(float ang);
    static Matriz4x4 cisalhaZY(float ang);
};

Matriz4x4 operator*(const Matriz4x4 &A, const Matriz4x4 &B);
Matriz4x4 operator+(const Matriz4x4 &A, const Matriz4x4 &B);
Matriz4x4 operator-(const Matriz4x4 &A, const Matriz4x4 &B);
Matriz4x4 operator*(const Matriz4x4 &M, float k);

Vetor operator*(const Matriz4x4 &M, const Vetor &v);

Ponto operator*(const Matriz4x4 &M, const Ponto &p);

#endif