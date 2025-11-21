#ifndef CUBO_HPP
#define CUBO_HPP

#include "../Malha/Malha.hpp"

struct Cubo : Malha
{
    Cubo(float tam_aresta, Ponto centro_base, Cor Kd, Cor Ke, Cor Ka, int M);

    void atualizarFaces();
    
    void transforma(const Matriz4x4 &M) override;

};

#endif