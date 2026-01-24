#ifndef MESA_HPP
#define MESA_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"

struct Mesa : ObjetoComplexo
{
    Paralelepipedo *base;
    Paralelepipedo *pedestal;
    Paralelepipedo *gaveteiro; // O novo compartimento
    Paralelepipedo *tampo;

    Mesa()
    {
        // =====================
        // Dimensões
        // =====================
        float ladoBase = 0.35f;       // Reduzida para não parecer pedestal
        float espessuraBase = 0.04f;

        float larguraPedestal = 0.12f;
        float alturaPedestal = 0.50f; // Altura da perna central

        float ladoGaveteiro = 0.55f;  // Compartimento onde ficam as gavetas
        float alturaGaveteiro = 0.12f;

        float ladoTampo = 0.8f;       // A "tábua" de jogo
        float espessuraTampo = 0.05f;

        Cor corMadeira(0.40f, 0.20f, 0.05f); // Marrom levemente mais escuro

        // =====================
        // 1. Base (No chão)
        // =====================
        Ponto posBase(0.0f, espessuraBase / 2.0f, 0.0f);
        base = new Paralelepipedo(ladoBase, ladoBase, espessuraBase, posBase, corMadeira, corMadeira, corMadeira, 10);

        // =====================
        // 2. Pedestal (Perna)
        // =====================
        float yPedestal = espessuraBase + (alturaPedestal / 2.0f);
        Ponto posPedestal(0.0f, yPedestal, 0.0f);
        pedestal = new Paralelepipedo(larguraPedestal, larguraPedestal, alturaPedestal, posPedestal, corMadeira, corMadeira, corMadeira, 10);

        // =====================
        // 3. Compartimento de Gavetas
        // =====================
        // Fica logo acima do pedestal e abaixo do tampo
        float yGaveteiro = espessuraBase + alturaPedestal + (alturaGaveteiro / 2.0f);
        Ponto posGaveteiro(0.0f, yGaveteiro, 0.0f);
        gaveteiro = new Paralelepipedo(ladoGaveteiro, ladoGaveteiro, alturaGaveteiro, posGaveteiro, corMadeira, corMadeira, corMadeira, 10);

        // =====================
        // 4. Tampo (Tábua da mesa)
        // =====================
        // Posicionado no topo de tudo
        float yTampo = espessuraBase + alturaPedestal + alturaGaveteiro + (espessuraTampo / 2.0f);
        Ponto posTampo(0.0f, yTampo, 0.0f);
        tampo = new Paralelepipedo(ladoTampo, ladoTampo, espessuraTampo, posTampo, corMadeira, corMadeira, corMadeira, 10);

        // Adicionar componentes na ordem de hierarquia
        adicionarComponente(base);
        adicionarComponente(pedestal);
        adicionarComponente(gaveteiro);
        adicionarComponente(tampo);
    }
};

#endif