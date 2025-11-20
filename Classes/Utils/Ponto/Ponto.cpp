#include "Ponto.hpp"

Ponto::Ponto(float x, float y, float z)
{
    Cord_x = x;
    Cord_y = y;
    Cord_z = z;
}

Ponto operator+(const Ponto &p1, const Ponto &p2)
{
    return Ponto(p1.Cord_x + p2.Cord_x,
                 p1.Cord_y + p2.Cord_y,
                 p1.Cord_z + p2.Cord_z);
}

Ponto operator*(const Ponto &p, float k)
{
    return Ponto(p.Cord_x * k,
                 p.Cord_y * k,
                 p.Cord_z * k);
}

Ponto operator*(float k, const Ponto &p)
{
    return p * k;
}

Ponto operator/(const Ponto &p, float k)
{
    return Ponto(p.Cord_x / k,
                 p.Cord_y / k,
                 p.Cord_z / k);
}