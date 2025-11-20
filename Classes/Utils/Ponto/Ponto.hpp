#ifndef PONTO_HPP
#define PONTO_HPP

using namespace std;

struct Ponto
{
    float Cord_x, Cord_y, Cord_z, Cord_w = 1.0f;

    Ponto(float x = 0, float y = 0, float z = 0);
};

Ponto operator+(const Ponto &p1, const Ponto &p2);

Ponto operator*(const Ponto &p, float k);

Ponto operator*(float k, const Ponto &p);

Ponto operator/(const Ponto &p, float k);

#endif