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
    Cilindro *peca1;
    Cilindro *peca2;
    Cilindro *peca3;
    Cilindro *peca4;
    Cilindro *peca5;
    Cilindro *peca6;
    Cilindro *peca7;
    Cilindro *peca8;

    Tabuleiro()
    {
        float ladosBase = 0.29f;
        float alturaBase = 0.03f;

        Ponto centroideBase = Ponto(0.0f, alturaBase / 2, 0.0f);

        base = new Paralelepipedo(ladosBase + 0.02f, ladosBase + 0.02f, alturaBase, centroideBase, Cor(0.65f, 0.47f, 0.31f), Cor(0.65f, 0.47f, 0.31f), Cor(0.65f, 0.47f, 0.31f), 100);

        string xadrezText = "../Assets/xadrez.png";

        float off = ladosBase / 2.0f;
        float yPeca = alturaBase + epsilon;

        Ponto minPt(-off, yPeca, -off);
        Ponto maxPt(off, yPeca, off);

        plano = new Plano(Ponto(0.0f, yPeca, 0.0f), Vetor(0.0f, 1.0f, 0.0f), xadrezText, 3.3f, 100, minPt, maxPt);

        adicionarComponente(base);
        adicionarComponente(plano);

        float q = ladosBase / 8.0f;

        peca1 = new Cilindro(Ponto(-off + 1.5f * q, yPeca, -off + 1.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), 100);

        peca2 = new Cilindro(Ponto(-off + 3.5f * q, yPeca, -off + 1.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), 100);

        peca3 = new Cilindro(Ponto(-off + 2.5f * q, yPeca, -off + 2.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), Cor(0.9f, 0.9f, 0.9f), 100);

        peca4 = new Cilindro(Ponto(-off + 3.5f * q, yPeca, -off + 3.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), 100);

        peca5 = new Cilindro(Ponto(-off + 5.5f * q, yPeca, -off + 5.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), 100);

        peca6 = new Cilindro(Ponto(-off + 7.5f * q, yPeca, -off + 7.5f * q), 0.015f, 0.01f, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), Cor(0.1f, 0.1f, 0.1f), 100);

        adicionarComponente(peca1);
        adicionarComponente(peca2);
        adicionarComponente(peca3);
        adicionarComponente(peca4);
        adicionarComponente(peca5);
        adicionarComponente(peca6);
    }
};

#endif