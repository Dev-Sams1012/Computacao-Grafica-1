#ifndef MALHA_HPP
#define MALHA_HPP

#include "../Triangulo/Triangulo.hpp"
#include "../ObjetoAbstrato/Objeto.hpp"

struct Malha : Objeto
{
    vector<Ponto> vertices;
    vector<Triangulo> faces;
    Vetor normal;

    Malha(vector<Ponto> vertices, vector<Triangulo> faces);

    Malha() = default;

    bool raioIntercepta(Ponto origem, Ponto canvas) override;

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override;

    void transforma(const Matriz4x4 &M) override;
};

#endif