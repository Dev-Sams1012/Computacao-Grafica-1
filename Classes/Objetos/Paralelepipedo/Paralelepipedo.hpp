#ifndef PARALELEPIPEDO_HPP
#define PARALELEPIPEDO_HPP

#include "../Malha/Malha.hpp"
#include "../../Utils/Matriz/Matriz4x4.hpp"

struct Paralelepipedo : Malha
{
    Paralelepipedo(float largura, float profundidade, float altura, Ponto centro,
                   Cor Kd, Cor Ke, Cor Ka, int M);

    void atualizarFaces();
    void Transforma(const Matriz4x4 &M);
};

#endif