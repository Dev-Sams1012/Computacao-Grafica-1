#ifndef BANQUETA_HPP
#define BANQUETA_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"

struct Banqueta : ObjetoComplexo
{
    Cilindro *assento;
    Paralelepipedo *pe1;
    Paralelepipedo *pe2;
    Paralelepipedo *pe3;
    Paralelepipedo *pe4;
    Paralelepipedo *haste1;
    Paralelepipedo *haste2;
    Paralelepipedo *haste3;
    Paralelepipedo *haste4;

    Banqueta()
    {
        float raioAssento = 0.20f;
        float alturaAssento = 0.05f;

        float ladoPe = 0.05f;
        float alturaPe = 0.40f;

        Cor corMadeira = Cor(0.30f, 0.15f, 0.05f);

        Ponto pAssento = Ponto(0.0f, alturaPe, 0.0f);

        assento = new Cilindro(pAssento, raioAssento, alturaAssento, Vetor(0.0f, 1.0f, 0.0f), true, true, corMadeira, corMadeira, corMadeira, 100);

        float yPos = alturaPe / 2.0f;

        Ponto pPe = Ponto(0.0f, -yPos, 0.0f);

        pe1 = new Paralelepipedo(ladoPe, ladoPe, alturaPe, pPe, corMadeira, corMadeira, corMadeira, 100);

        pe2 = new Paralelepipedo(ladoPe, ladoPe, alturaPe, pPe, corMadeira, corMadeira, corMadeira, 100);

        pe3 = new Paralelepipedo(ladoPe, ladoPe, alturaPe, pPe, corMadeira, corMadeira, corMadeira, 100);

        pe4 = new Paralelepipedo(ladoPe, ladoPe, alturaPe, pPe, corMadeira, corMadeira, corMadeira, 100);

        float sh = 0.1f;

        Matriz4x4 mX = Matriz4x4::cisalhaXY(sh);
        Matriz4x4 mZ = Matriz4x4::cisalhaZY(sh);

        Matriz4x4 mX_inv = Matriz4x4::cisalhaXY(-sh);
        Matriz4x4 mZ_inv = Matriz4x4::cisalhaZY(-sh);

        Matriz4x4 cisalha1 = mX * mZ;
        Matriz4x4 cisalha2 = mX_inv * mZ;
        Matriz4x4 cisalha3 = mX * mZ_inv;
        Matriz4x4 cisalha4 = mX_inv * mZ_inv;

        float offset = 0.11f;

        Matriz4x4 translada1 = Matriz4x4::translacao(-offset, alturaPe, -offset);
        pe1->transforma(translada1 * cisalha1);

        Matriz4x4 translada2 = Matriz4x4::translacao(offset, alturaPe, -offset);
        pe2->transforma(translada2 * cisalha2);

        Matriz4x4 translada3 = Matriz4x4::translacao(-offset, alturaPe, offset);
        pe3->transforma(translada3 * cisalha3);

        Matriz4x4 translada4 = Matriz4x4::translacao(offset, alturaPe, offset);
        pe4->transforma(translada4 * cisalha4);

        float distHaste = 0.15f;
        float comprHaste = 0.28f;
        float ladoHaste = 0.02f;
        float desloca = 0.025f;

        haste1 = new Paralelepipedo(comprHaste, ladoHaste, ladoHaste, Ponto(0.0f, distHaste, -offset - desloca), corMadeira, corMadeira, corMadeira, 100);

        haste2 = new Paralelepipedo(comprHaste, ladoHaste, ladoHaste, Ponto(0.0f, distHaste, offset + desloca), corMadeira, corMadeira, corMadeira, 100);

        haste3 = new Paralelepipedo(ladoHaste, comprHaste, ladoHaste, Ponto(-offset - desloca, distHaste, 0.0f), corMadeira, corMadeira, corMadeira, 100);

        haste4 = new Paralelepipedo(ladoHaste, comprHaste, ladoHaste, Ponto(offset + desloca, distHaste, 0.0f), corMadeira, corMadeira, corMadeira, 100);

        adicionarComponente(assento);
        adicionarComponente(pe1);
        adicionarComponente(pe2);
        adicionarComponente(pe3);
        adicionarComponente(pe4);
        adicionarComponente(haste1);
        adicionarComponente(haste2);
        adicionarComponente(haste3);
        adicionarComponente(haste4);
    }
};

#endif