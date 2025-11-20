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

    bool raioIntercepta(Ponto origem, Ponto canvas) override;

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override;
};

#endif