#ifndef BANCO_HPP
#define BANCO_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"

struct Banco : ObjetoComplexo
{
    Paralelepipedo *assento;
    Paralelepipedo *encosto;
    Cilindro *perna1, *perna2, *perna3, *perna4;

    Banco()
    {
        // =====================
        // Dimensões
        // =====================
        float largura = 2.0f;
        float profundidade = 0.6f;
        float espessura = 0.08f;
        float alturaAssentoY = 0.45f; // Altura do topo do assento
        float alturaEncosto = 0.5f;
        float raioPerna = 0.03f;

        // A altura da perna vai do chão (0.0) até a base inferior do assento
        float alturaPerna = alturaAssentoY - espessura; 
        
        Cor corMadeira(0.55f, 0.27f, 0.07f);
        Cor corFerro(0.2f, 0.2f, 0.2f);

        // =====================
        // Assento
        // =====================
        // Posicionado para que o TOPO fique em alturaAssentoY
        Ponto posAssento(0.0f, alturaAssentoY - (espessura / 2.0f), 0.0f);
        assento = new Paralelepipedo(largura, profundidade, espessura, posAssento, corMadeira, corMadeira, corMadeira, 10);

        // =====================
        // Encosto
        // =====================
        // Posicionado na borda traseira e acima do assento
        float zEncosto = (profundidade / 2.0f) - (espessura / 2.0f);
        float yEncosto = alturaAssentoY + (alturaEncosto / 2.0f);
        Ponto posEncosto(0.0f, yEncosto, zEncosto);
        encosto = new Paralelepipedo(largura, espessura, alturaEncosto, posEncosto, corMadeira, corMadeira, corMadeira, 10);

        // =====================
        // Pernas (Cilindros)
        // =====================
        // Seguindo o modelo do poste: Ponto base, raio, altura, direção
        // O ponto base deve ser o chão (Y = 0.0)
        Vetor up(0.0f, 1.0f, 0.0f);
        float dx = (largura / 2.0f) - 0.1f;
        float dz = (profundidade / 2.0f) - 0.1f;

        perna1 = new Cilindro(Ponto(-dx, 0.0f, -dz), raioPerna, alturaPerna, up, true, true, corFerro, corFerro, corFerro, 10);
        perna2 = new Cilindro(Ponto(dx, 0.0f, -dz), raioPerna, alturaPerna, up, true, true, corFerro, corFerro, corFerro, 10);
        perna3 = new Cilindro(Ponto(-dx, 0.0f, dz), raioPerna, alturaPerna, up, true, true, corFerro, corFerro, corFerro, 10);
        perna4 = new Cilindro(Ponto(dx, 0.0f, dz), raioPerna, alturaPerna, up, true, true, corFerro, corFerro, corFerro, 10);

        adicionarComponente(assento);
        adicionarComponente(encosto);
        adicionarComponente(perna1);
        adicionarComponente(perna2);
        adicionarComponente(perna3);
        adicionarComponente(perna4);
    }
};

#endif