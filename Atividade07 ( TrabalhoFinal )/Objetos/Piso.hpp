#ifndef PISO_HPP
#define PISO_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../../Classes/Objetos/Plano/Plano.hpp"

struct Piso : ObjetoComplexo
{
    Cilindro *area;
    Plano *pedra;
    Piso()
    {
        string pedraText = "../Assets/caminho-de-pedras.png";
        Cor kd_pedra = Cor(0.48f, 0.50f, 0.53f);
        Cor ke_pedra = Cor(0.1f, 0.1f, 0.1f);
        Cor ka_pedra = Cor(0.2f, 0.2f, 0.2f);
        float m_pedra = 30;

        Vetor up(0, 1, 0);

        float rBase = 6.0f;
        float hBase = 0.02f;
        float rIntBase = 1.67f;

        area = new Cilindro(Ponto(0, 0, 0), rBase, rIntBase, hBase, up, false, false, kd_pedra, ke_pedra, ka_pedra, m_pedra);

        adicionarComponente(area);

        pedra = new Plano(Ponto(0,hBase + epsilon,0), up, pedraText, 0.45, m_pedra, rBase);
        adicionarComponente(pedra);
    }
};

#endif