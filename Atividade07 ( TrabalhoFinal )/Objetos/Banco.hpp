#ifndef BANCO_HPP
#define BANCO_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"

struct Banco : ObjetoComplexo
{
    Paralelepipedo *assento;
    Paralelepipedo *encosto;
    Cilindro *perna1;
    Cilindro *perna2;
    Cilindro *perna3;
    Cilindro *perna4;

    Banco()
    {
        // =====================
        // Assento
        // =====================
        assento = new Paralelepipedo(
            2.0f, 0.2f, 0.6f,
            Ponto(0.0f, 0.6f, 0.0f),
            Cor(0.55f, 0.27f, 0.07f),
            Cor(0.55f, 0.27f, 0.07f),
            Cor(0.55f, 0.27f, 0.07f),
            10
        );

        // =====================
        // Encosto
        // =====================
        encosto = new Paralelepipedo(
            2.0f, 0.8f, 0.2f,
            Ponto(0.0f, 1.1f, -0.25f),
            Cor(0.50f, 0.25f, 0.05f),
            Cor(0.50f, 0.25f, 0.05f),
            Cor(0.50f, 0.25f, 0.05f),
            10
        );

        // =====================
        // Pernas
        // =====================
        float raioPerna = 0.05f;
        float alturaPerna = 0.6f;

        perna1 = new Cilindro(Ponto(-0.9f, 0.3f, -0.25f), raioPerna, alturaPerna, Vetor(0.0f, 1.0f, 0.0f),
                              true, true,
                              Cor(0.2f, 0.2f, 0.2f),
                              Cor(0.2f, 0.2f, 0.2f),
                              Cor(0.2f, 0.2f, 0.2f),
                              10);

        perna2 = new Cilindro(Ponto(0.9f, 0.3f, -0.25f), raioPerna, alturaPerna, Vetor(0.0f, 1.0f, 0.0f),
                              true, true,
                              Cor(0.2f, 0.2f, 0.2f),
                              Cor(0.2f, 0.2f, 0.2f),
                              Cor(0.2f, 0.2f, 0.2f),
                              10);

        perna3 = new Cilindro(Ponto(-0.9f, 0.3f, 0.25f), raioPerna, alturaPerna, Vetor(0.0f, 1.0f, 0.0f),
                              true, true,
                              Cor(0.2f, 0.2f, 0.2f),
                              Cor(0.2f, 0.2f, 0.2f),
                              Cor(0.2f, 0.2f, 0.2f),
                              10);

        perna4 = new Cilindro(Ponto(0.9f, 0.3f, 0.25f), raioPerna, alturaPerna, Vetor(0.0f, 1.0f, 0.0f),
                              true, true,
                              Cor(0.2f, 0.2f, 0.2f),
                              Cor(0.2f, 0.2f, 0.2f),
                              Cor(0.2f, 0.2f, 0.2f),
                              10);

        // =====================
        // Adiciona componentes
        // =====================
        adicionarComponente(assento);
        adicionarComponente(encosto);
        adicionarComponente(perna1);
        adicionarComponente(perna2);
        adicionarComponente(perna3);
        adicionarComponente(perna4);
    }
};

#endif