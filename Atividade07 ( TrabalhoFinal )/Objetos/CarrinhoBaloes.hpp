#ifndef CARRINHO_BALOES_HPP
#define CARRINHO_BALOES_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../../Classes/Objetos/Esfera/Esfera.hpp"
#include "../../Classes/Utils/Matriz/Matriz4x4.hpp"
#include <cmath>

struct CarrinhoBaloes : ObjetoComplexo
{
    Paralelepipedo *corpo;
    Paralelepipedo *tampo; 
    Cilindro *aroL, *aroR, *cuboL, *cuboR;
    Cilindro *raiosL[8], *raiosR[8];
    Cilindro *apoioTrasL, *apoioTrasR, *hasteL, *hasteR, *barraMao;
    Cilindro *cordaoV, *cordaoG, *cordaoB;
    Esfera *balaoV, *balaoG, *balaoB;

    CarrinhoBaloes()
    {
        Cor vermelho(0.8f, 0.1f, 0.1f), verde(0.1f, 0.7f, 0.1f), azul(0.1f, 0.1f, 0.8f);
        Cor metal(0.4f, 0.4f, 0.4f), preto(0.05f, 0.05f, 0.05f), branco(0.9f, 0.9f, 0.9f);
        Cor madeiraClara(0.9f, 0.8f, 0.6f);

        float largCorpo = 0.6f, altCorpo = 0.5f, profCorpo = 0.8f;
        float vaoLivre = 0.25f;
        float espessuraTampo = 0.04f;

        // 1. CORPO
        Ponto centroCorpo(0.0f, vaoLivre + (altCorpo / 2.0f), 0.0f);
        corpo = new Paralelepipedo(largCorpo, profCorpo, altCorpo, centroCorpo, vermelho, vermelho, vermelho, 10);
        adicionarComponente(corpo);

        // 1.1 TAMPO
        Ponto centroTampo(0.0f, vaoLivre + altCorpo + (espessuraTampo / 2.0f), 0.0f);
        tampo = new Paralelepipedo(largCorpo + 0.1f, profCorpo + 0.1f, espessuraTampo, centroTampo, madeiraClara, madeiraClara, madeiraClara, 10);
        adicionarComponente(tampo);

        // 2. RODAS FRONTAIS
        float raioRoda = 0.22f, largRoda = 0.06f, raioCubo = 0.03f, zRoda = -profCorpo / 3.0f;
        Vetor dirEixo(1.0f, 0.0f, 0.0f);
        for (int lado : {-1, 1}) {
            float xRoda = lado * (largCorpo / 2.0f + 0.04f);
            Ponto centroRoda(xRoda, raioRoda, zRoda);
            Ponto pBaseCil(centroRoda.Cord_x - (largRoda / 2.0f), centroRoda.Cord_y, centroRoda.Cord_z);
            Cilindro* aro = new Cilindro(pBaseCil, raioRoda, raioRoda - 0.02f, largRoda, dirEixo, true, true, true, preto, preto, preto, 10);
            Cilindro* cubo = new Cilindro(pBaseCil, raioCubo, 0.0f, largRoda, dirEixo, true, true, false, metal, metal, metal, 10);
            if (lado == -1) { aroL = aro; cuboL = cubo; } else { aroR = aro; cuboR = cubo; }
            adicionarComponente(aro); adicionarComponente(cubo);
            for (int i = 0; i < 8; i++) {
                float ang = i * (M_PI / 4.0f);
                Vetor dR(0.0f, cos(ang), sin(ang));
                Ponto pI(centroRoda.Cord_x, centroRoda.Cord_y + dR.Cord_y * raioCubo, centroRoda.Cord_z + dR.Cord_z * raioCubo);
                Cilindro* raio = new Cilindro(pI, 0.008f, raioRoda - raioCubo - 0.01f, dR, true, true, metal, metal, metal, 10);
                if (lado == -1) raiosL[i] = raio; else raiosR[i] = raio;
                adicionarComponente(raio);
            }
        }

        // 3. APOIOS TRASEIROS
        float zApoio = profCorpo / 2.0f - 0.1f;
        apoioTrasL = new Cilindro(Ponto(-largCorpo/4.0f, 0.0f, zApoio), 0.025f, vaoLivre, Vetor(0,1,0), true, true, metal, metal, metal, 10);
        apoioTrasR = new Cilindro(Ponto(largCorpo/4.0f, 0.0f, zApoio), 0.025f, vaoLivre, Vetor(0,1,0), true, true, metal, metal, metal, 10);
        adicionarComponente(apoioTrasL); adicionarComponente(apoioTrasR);

        // 4. HASTE
        float angH = 0.7f; Vetor dH(0.0f, cos(angH), sin(angH)); float lenH = 0.45f;
        Ponto pIL(-largCorpo/2.0f, vaoLivre + altCorpo, profCorpo/2.0f);
        Ponto pIR(largCorpo/2.0f, vaoLivre + altCorpo, profCorpo/2.0f);
        hasteL = new Cilindro(pIL, 0.015f, lenH, dH, true, true, metal, metal, metal, 10);
        hasteR = new Cilindro(pIR, 0.015f, lenH, dH, true, true, metal, metal, metal, 10);
        Ponto pFL(pIL.Cord_x, pIL.Cord_y + dH.Cord_y * lenH, pIL.Cord_z + dH.Cord_z * lenH);
        barraMao = new Cilindro(Ponto(pFL.Cord_x - 0.05f, pFL.Cord_y, pFL.Cord_z), 0.025f, largCorpo + 0.1f, Vetor(1,0,0), true, true, preto, preto, preto, 10);
        adicionarComponente(hasteL); adicionarComponente(hasteR); adicionarComponente(barraMao);

        // 5. BALÕES CORRIGIDOS
        Ponto pFix(0.0f, vaoLivre + altCorpo + espessuraTampo, -profCorpo/2.0f + 0.1f);
        float lenC = 1.1f, rB = 0.16f;

        auto criaBalao = [&](Vetor dir, Cor c, Cilindro*& cord, Esfera*& bal) {
            dir = normalizar(dir);
            
            // Criar o cordão
            cord = new Cilindro(pFix, 0.004f, lenC, dir, true, true, branco, branco, branco, 10);
            
            // Escala para formato de balão (Y maior que X e Z)
            float escalaY = 1.4f;
            float escalaXZ = 0.9f;
            
            // CRIAR NA ORIGEM (0,0,0) - Essencial para a escala não deslocar o objeto
            bal = new Esfera(Ponto(0,0,0), rB, c, c, c, 50);
            
            // Matriz de Escala
            Matriz4x4 S = Matriz4x4::escala(escalaXZ, escalaY, escalaXZ);
            
            // Posicionamento: Distância do cordão + metade da altura escalada da esfera
            float distCentro = lenC + (rB * escalaY);
            Ponto pCentro(pFix.Cord_x + dir.Cord_x * distCentro, 
                          pFix.Cord_y + dir.Cord_y * distCentro, 
                          pFix.Cord_z + dir.Cord_z * distCentro);
            
            // Matriz de Translação
            Matriz4x4 T = Matriz4x4::translacao(pCentro.Cord_x, pCentro.Cord_y, pCentro.Cord_z);
            
            // Transforma: Primeiro escala (no centro), depois move para o topo do cordão
            bal->transforma(T * S);
        };

        criaBalao(Vetor(-0.2f, 0.95f, 0.1f), vermelho, cordaoV, balaoV);
        criaBalao(Vetor(0.0f, 1.0f, 0.0f), verde, cordaoG, balaoG);
        criaBalao(Vetor(0.2f, 0.95f, -0.1f), azul, cordaoB, balaoB);

        adicionarComponente(cordaoV); adicionarComponente(balaoV);
        adicionarComponente(cordaoG); adicionarComponente(balaoG);
        adicionarComponente(cordaoB); adicionarComponente(balaoB);
    }
};

#endif