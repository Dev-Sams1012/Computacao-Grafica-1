#ifndef LUZ_HPP
#define LUZ_HPP

#include "../Janela/Janela.hpp"
#include "../Ponto/Ponto.hpp"

struct Luz
{
    Ponto PF;
    Cor IF;
    Cor IA;

    Luz(Ponto PF, Cor IF, Cor IA);
};

#endif