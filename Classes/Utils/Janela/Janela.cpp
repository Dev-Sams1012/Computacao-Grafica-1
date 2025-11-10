#include "Janela.hpp"

Cor::Cor(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Cor operadorArroba(Cor a, Cor b)
{
    return {a.r * b.r, a.g * b.g, a.b * b.b};
}

Janela::Janela(float w, float h, float d)
{
    this->w = w;
    this->h = h;
    this->d = d;
}