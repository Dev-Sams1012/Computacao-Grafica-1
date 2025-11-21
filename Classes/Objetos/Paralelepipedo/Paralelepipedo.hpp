#ifndef PARALELEPIPEDO_HPP
#define PARALELEPIPEDO_HPP

#include "../Malha/Malha.hpp"

struct Paralelepipedo : Malha
{
    float largura;
    float profundidade;
    float altura;
    Ponto centro;

    Paralelepipedo(float largura, float profundidade, float altura, Ponto centro, Cor Kd, Cor Ke, Cor Ka, int M);

    void atualizarFaces();
    void transforma(const Matriz4x4 &M) override;
};

#endif