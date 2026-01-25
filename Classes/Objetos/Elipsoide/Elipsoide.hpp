#ifndef ELIPSOIDE_HPP
#define ELIPSOIDE_HPP

#include "../ObjetoAbstrato/Objeto.hpp"

struct Elipsoide : public Objeto
{
    Ponto centro;
    float r1, r2, r3;

    Elipsoide(Ponto c, float R1, float R2, float R3, Cor Kd, Cor Ke, Cor Ka, int M);

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit) override;

    Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;

    string getNomeObj() const override { return "Elipsoide"; }
};

#endif