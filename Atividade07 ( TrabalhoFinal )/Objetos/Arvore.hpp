#ifndef ARVORE_HPP
#define ARVORE_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../../Classes/Objetos/Elipsoide/Elipsoide.hpp"
#include "../../Classes/Objetos/Esfera/Esfera.hpp"

struct Arvore : ObjetoComplexo
{
    Cilindro *tronco;
    Cilindro *galho1, *galho2, *galho3, *galho4, *galho5;
    Elipsoide *principal, *copa1, *copa2, *copa3;
    Esfera *fruto1, *fruto2;

    Arvore()
    {
        Cor marromEscuro(0.35f, 0.20f, 0.10f);
        Cor marromMedio(0.45f, 0.30f, 0.15f);
        Cor verdeFloresta(0.10f, 0.35f, 0.10f);
        Cor vermelhoFruto(0.80f, 0.05f, 0.05f);

        tronco = new Cilindro(Ponto(0, 0, 0), 0.18f, 1.8f, Vetor(0, 1, 0), true, true, marromEscuro, marromEscuro, marromEscuro, 10);
        adicionarComponente(tronco);

        galho1 = new Cilindro(Ponto(0, 1.2f, 0), 0.10f, 0.7f, normalizar(Vetor( 0.4f, 0.8f,  0.2f)), true, true, marromMedio, marromMedio, marromMedio, 10);
        galho2 = new Cilindro(Ponto(0, 1.1f, 0), 0.09f, 0.6f, normalizar(Vetor(-0.5f, 0.7f, -0.1f)), true, true, marromMedio, marromMedio, marromMedio, 10);
        galho3 = new Cilindro(Ponto(0, 1.3f, 0), 0.08f, 0.5f, normalizar(Vetor( 0.1f, 0.9f, -0.4f)), true, true, marromMedio, marromMedio, marromMedio, 10);
        galho4 = new Cilindro(Ponto(0, 0.8f, 0), 0.07f, 0.4f, normalizar(Vetor(-0.2f, 0.5f,  0.5f)), true, true, marromMedio, marromMedio, marromMedio, 10);
        galho5 = new Cilindro(Ponto(0, 1.0f, 0), 0.07f, 0.4f, normalizar(Vetor( 0.5f, 0.4f, -0.3f)), true, true, marromMedio, marromMedio, marromMedio, 10);

        adicionarComponente(galho1); adicionarComponente(galho2); adicionarComponente(galho3);
        adicionarComponente(galho4); adicionarComponente(galho5);

        principal = new Elipsoide(Ponto(0, 2.2f, 0), 1.0f, 0.7f, 1.0f, verdeFloresta, verdeFloresta, verdeFloresta, 50);
        adicionarComponente(principal);

        copa1 = new Elipsoide(Ponto(0.4f, 1.8f, 0.3f), 0.6f, 0.5f, 0.6f, verdeFloresta, verdeFloresta, verdeFloresta, 100);
        copa2 = new Elipsoide(Ponto(-0.5f, 1.9f, -0.4f), 0.5f, 0.4f, 0.5f, verdeFloresta, verdeFloresta, verdeFloresta, 50);
        copa3 = new Elipsoide(Ponto(0.1f, 2.5f, -0.2f), 0.7f, 0.5f, 0.7f, verdeFloresta, verdeFloresta, verdeFloresta, 150);

        adicionarComponente(copa1); adicionarComponente(copa2); adicionarComponente(copa3);

        fruto1 = new Esfera(Ponto(0.5f, 1.3f, 0.4f), 0.06f, vermelhoFruto, vermelhoFruto, vermelhoFruto, 100);
        fruto2 = new Esfera(Ponto(-0.3f, 1.7f, 0.6f), 0.06f, vermelhoFruto, vermelhoFruto, vermelhoFruto, 100);

        adicionarComponente(fruto1); adicionarComponente(fruto2);
    }
};

#endif