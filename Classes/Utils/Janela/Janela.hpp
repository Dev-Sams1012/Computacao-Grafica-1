#ifndef JANELA_HPP
#define JANELA_HPP

using namespace std;

struct Cor
{
    float r, g, b;

    Cor(float r = 0.0f, float g = 0.0f, float b = 0.0f);
};

Cor operadorArroba(Cor a, Cor b);

struct Janela
{
    float w, h, d;

    Janela(float w = 0.0f, float h = 0.0f, float d = 0.0f);
};

#endif
