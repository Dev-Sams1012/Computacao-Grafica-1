#ifndef LIXEIRA_HPP
#define LIXEIRA_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "../../Classes/Objetos/Cone/Cone.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"

struct lixeira : ObjetoComplexo {
    Cilindro* corpo;
    Cone* tampa;
    Cilindro* hasteEsquerda;
    Cilindro* hasteDireita;

    lixeira(Cor cor) {
        float rLata = 0.15f;
        float rInt = 0.13f;
        float altLata = 0.5f;
        float altFlut = 0.15f;
        float yTampa = altLata + altFlut;
        
        float dxH = 0.14f;
        float raioHaste = 0.012f;
        float compHaste = altFlut;
        
        Cor metal(0.3f, 0.3f, 0.3f);
        Vetor up(0, 1, 0);

        corpo = new Cilindro(Ponto(0, 0, 0), rLata, rInt, altLata, up, true, false, cor, cor, cor, 20);
        adicionarComponente(corpo);
        
        tampa = new Cone(Ponto(0, yTampa, 0), rLata + 0.02f, 0.15f, 0.10f, up, true, true, cor, cor, cor, 20);
        adicionarComponente(tampa);

        hasteEsquerda = new Cilindro(Ponto(-dxH, altLata, 0.0), raioHaste, compHaste, up, true, true, metal, metal, metal, 10);
        adicionarComponente(hasteEsquerda);

        hasteDireita = new Cilindro(Ponto(dxH, altLata, 0.0), raioHaste, compHaste, up, true, true, metal, metal, metal, 10);
        adicionarComponente(hasteDireita);
    }
};

#endif