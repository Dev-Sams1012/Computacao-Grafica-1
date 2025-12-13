#ifndef ESFERA_HPP
#define ESFERA_HPP

#include "../ObjetoAbstrato/Objeto.hpp"

struct Esfera : public Objeto
{
    Ponto centro;
    float raio;

    Esfera(Ponto c, float r, Cor Kd, Cor Ke, Cor Ka, int M);

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr) override;

    Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;
};

#endif