#ifndef CONE_HPP
#define CONE_HPP

#include "../ObjetoAbstrato/Objeto.hpp"

struct Cone : public Objeto
{
    Ponto Centro_base;
    Ponto Vertice_topo;
    float Raio_base;
    float Altura;
    float Altura_corte;
    Vetor Eixo;

    bool TemBase;
    bool TemTampaSuperior; //tampa do corte

    Matriz3x3 Q_Matrix;
    Matriz3x3 M_Matrix;

    Cone(Ponto Cb, float Rb, float H, Vetor dr, bool temBase, Cor Kd, Cor Ke, Cor Ka, int M);

    Cone(Ponto Cb, float Rb, float H, float H_corte, Vetor dr, bool temBase, bool temTampaSup, Cor Kd, Cor Ke, Cor Ka, int M);

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit) override;

    Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;

    string getNomeObj() const override { return "Cone"; }
};

#endif