#ifndef PONTO_HPP
#define PONTO_HPP

using namespace std;

struct Ponto
{
    float Cord_x, Cord_y, Cord_z, Cord_w = 1.0f;

    Ponto(float x = 0, float y = 0, float z = 0);
};

Ponto operator+(Ponto p1, Ponto p2);

Ponto operator*(Ponto p, float k);

Ponto operator*(float k, Ponto p);

Ponto operator/(Ponto p, float k);

#endif