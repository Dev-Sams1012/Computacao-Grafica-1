#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "../../Classes/Objetos/Plano/Plano.hpp"

struct Tabuleiro : ObjetoComplexo
{
    Paralelepipedo *base;
    Plano *plano;
    Cilindro *peça1;
    Cilindro *peça2;
    Cilindro *peça3;
    Cilindro *peça4;
    Cilindro *peça5;
    Cilindro *peça6;
    Cilindro *peça7;
    Cilindro *peça8;

    Tabuleiro()
    {
        float ladosBase = 0.29f;
        float alturaBase = 0.03f;

        Ponto centroideBase = Ponto(0.0f, alturaBase / 2, 0.0f);

        base = new Paralelepipedo(ladosBase + 0.02f, ladosBase + 0.02f, alturaBase, centroideBase, Cor(0.65f, 0.47f, 0.31f), Cor(0.65f, 0.47f, 0.31f), Cor(0.65f, 0.47f, 0.31f), 100);

        string xadrezText = "../Assets/xadrez.png";

        float off = ladosBase / 2.0f;
        float yPeça = alturaBase + epsilon;

        Ponto minPt(-off, yPeça, -off);
        Ponto maxPt(off, yPeça, off);

        plano = new Plano(Ponto(0.0f, yPeça, 0.0f), Vetor(0.0f, 1.0f, 0.0f), xadrezText, 3.3f, 100, minPt, maxPt);

        adicionarComponente(base);
        adicionarComponente(plano);

        float q = ladosBase / 8.0f;

        peça1 = new Cilindro(Ponto(-off + 1.5f * q, yPeça, -off + 1.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), 100);

        peça2 = new Cilindro(Ponto(-off + 3.5f * q, yPeça, -off + 1.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), 100);

        peça3 = new Cilindro(Ponto(-off + 2.5f * q, yPeça, -off + 2.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), 100);

        peça4 = new Cilindro(Ponto(-off + 3.5f * q, yPeça, -off + 3.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), 100);

        peça5 = new Cilindro(Ponto(-off + 5.5f * q, yPeça, -off + 5.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), 100);

        peça6 = new Cilindro(Ponto(-off + 7.5f * q, yPeça, -off + 7.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), 100);

        adicionarComponente(peça1);
        adicionarComponente(peça2);
        adicionarComponente(peça3);
        adicionarComponente(peça4);
        adicionarComponente(peça5);
        adicionarComponente(peça6);
    }
};

#endif