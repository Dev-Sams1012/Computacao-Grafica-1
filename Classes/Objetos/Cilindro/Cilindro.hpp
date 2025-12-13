#ifndef CILINDRO_HPP
#define CILINDRO_HPP

#include "../ObjetoAbstrato/Objeto.hpp"

struct Cilindro : public Objeto
{
    Ponto Centro_base;
    float Raio_base;
    float Altura;
    Vetor Eixo;
    Matriz3x3 Q_Matrix;
    Matriz3x3 M_Matrix;
    bool temBaseInferior;
    bool temBaseSuperior;

    Cilindro(Ponto Cb, float Rb, float H, Vetor dr, bool TemBaseInf, bool TemBaseSup, Cor Kd, Cor Ke, Cor Ka, int m_cor);

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr) override;

    Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;
};

#endif