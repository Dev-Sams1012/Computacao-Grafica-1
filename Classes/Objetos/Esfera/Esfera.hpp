#ifndef ESFERA_HPP
#define ESFERA_HPP

#include "../ObjetoAbstrato/Objeto.hpp"

struct Esfera : public Objeto
{
    Ponto centro;
    float raio;
    bool ehSemiesfera;
    bool inverterCorte;

    Esfera(Ponto c, float r, Cor Kd, Cor Ke, Cor Ka, int M, bool semi = false, bool inverter = false);

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit) override;

    Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;

    string getNomeObj() const override { return "Esfera"; }
};

#endif