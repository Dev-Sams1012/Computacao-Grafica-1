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

    bool raioIntercepta(Ponto origem, Ponto canvas) override;

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override;
};

#endif