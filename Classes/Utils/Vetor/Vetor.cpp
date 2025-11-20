#include "Vetor.hpp"
#include <cmath>

Vetor::Vetor(float x, float y , float z)
{
    Cord_x = x;
    Cord_y = y;
    Cord_z = z;
}

float Vetor::norma(){
    return sqrtf(Cord_x * Cord_x + Cord_y * Cord_y + Cord_z * Cord_z);
}

Vetor normalizar(const Vetor &v)
{
    float norma = sqrtf(v.Cord_x * v.Cord_x + v.Cord_y * v.Cord_y + v.Cord_z * v.Cord_z);
    return Vetor(v.Cord_x / norma, v.Cord_y / norma, v.Cord_z / norma);
}

float produtoEscalar(const Vetor &v1, const Vetor &v2)
{
    return (v1.Cord_x * v2.Cord_x + v1.Cord_y * v2.Cord_y + v1.Cord_z * v2.Cord_z);
}

Vetor produtoVetorial(const Vetor &v1, const Vetor &v2)
{
    return Vetor(v1.Cord_y * v2.Cord_z - v1.Cord_z * v2.Cord_y,
                 v1.Cord_z * v2.Cord_x - v1.Cord_x * v2.Cord_z,
                 v1.Cord_x * v2.Cord_y - v1.Cord_y * v2.Cord_x);
}

Ponto ray(const Ponto &p, const Vetor &v, float t)
{
    return Ponto(p.Cord_x + v.Cord_x * t,
                 p.Cord_y + v.Cord_y * t,
                 p.Cord_z + v.Cord_z * t);
}

Vetor operator-(const Ponto &p2, const Ponto &p1)
{
    return Vetor(p2.Cord_x - p1.Cord_x, p2.Cord_y - p1.Cord_y, p2.Cord_z - p1.Cord_z);
}

Vetor operator-(const Vetor &v1, const Vetor &v2)
{
    return Vetor(v1.Cord_x - v2.Cord_x, v1.Cord_y - v2.Cord_y, v1.Cord_z - v2.Cord_z);
}

Vetor operator-(const Vetor &v)
{
    return Vetor(-v.Cord_x, -v.Cord_y, -v.Cord_z);
}

Vetor operator+(const Vetor &v1, const Vetor &v2)
{
    return Vetor(v1.Cord_x + v2.Cord_x, v1.Cord_y + v2.Cord_y, v1.Cord_z + v2.Cord_z);
}

Vetor operator*(float k, const Vetor &v)
{
    return Vetor(v.Cord_x * k, v.Cord_y * k, v.Cord_z * k);
}

Vetor operator*(const Vetor &v, float k)
{
    return k * v;
}

Vetor operator/(const Vetor &v, float k)
{
    return Vetor(v.Cord_x / k, v.Cord_y / k, v.Cord_z / k);
}
