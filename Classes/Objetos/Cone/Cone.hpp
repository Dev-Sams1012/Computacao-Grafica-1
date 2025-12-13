#ifndef CONE_HPP
#define CONE_HPP

#include "../ObjetoAbstrato/Objeto.hpp"

struct Cone : public Objeto
{
    Ponto Centro_base;
    Ponto Vertice_topo;
    float Raio_base;
    float Altura;
    Vetor Eixo;
    Matriz3x3 Q_Matrix;
    Matriz3x3 M_Matrix;
    bool TemBase;

    Cone(Ponto Cb, float Rb, float H, Vetor dr,  bool temBase, Cor Kd, Cor Ke, Cor Ka, int M);

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr) override;

    Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;
};

#endif