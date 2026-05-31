#ifndef CUBO_HPP
#define CUBO_HPP

#include "../Malha/Malha.hpp"

struct Cubo : Malha
{
    float tam_aresta;
    Ponto centro_base;

    Cubo(float tam_aresta, Ponto centro_base, Cor Kd, Cor Ke, Cor Ka, int M);

    Cubo(float tam_aresta, Ponto centro_base, string arquivoTextura, float escala, int M);

    void atualizarFaces();
    
    void transforma(const Matriz4x4 &M) override;

    string getNomeObj() const override { return "Cubo"; }

};

#endif