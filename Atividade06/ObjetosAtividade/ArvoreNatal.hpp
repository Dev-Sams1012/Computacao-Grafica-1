#ifndef ARVORE_NATAL_HPP
#define ARVORE_NATAL_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../../Classes/Objetos/Esfera/Esfera.hpp"
#include "../../Classes/Objetos/Cone/Cone.hpp"

struct ArvoreNatal : public ObjetoComplexo
{
    Cilindro *suporte;
    Cilindro *tronco;
    Cone *folhagem;
    Esfera *bola;

    ArvoreNatal()
    {
        float raioSuporte = 0.3f;
        float alturaSuporte = 0.09f;

        float raioTronco = 0.06f;
        float alturaTronco = 0.4f;

        float raioFolhagem = 0.6f;
        float alturaFolhagem = 1.5f;

        float raioBola = 0.045f;

        float ySuporteInferior = -0.8f;

        Ponto centroSuporte = Ponto(0.0f, ySuporteInferior, -2.0f);

        Ponto centroTronco = Ponto(0.0f, ySuporteInferior + alturaSuporte, -2.0f);

        Ponto centroFolhagem = Ponto(0.0f, ySuporteInferior + alturaSuporte + alturaTronco, -2.0f);

        Ponto centroBola = Ponto(0.0f, ySuporteInferior + alturaSuporte + alturaTronco + alturaFolhagem + raioBola, -2.0f);

        suporte = new Cilindro(centroSuporte, raioSuporte, alturaSuporte, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.5f, 0.5f, 0.5f), Cor(0.5f, 0.5f, 0.5f), Cor(0.5f, 0.5f, 0.5f), 10);

        tronco = new Cilindro(centroTronco, raioTronco, alturaTronco, Vetor(0.0f, 1.0f, 0.0f), true, true, Cor(0.55f, 0.27f, 0.07f), Cor(0.55f, 0.27f, 0.07f), Cor(0.55f, 0.27f, 0.07f), 10);

        folhagem = new Cone(centroFolhagem, raioFolhagem, alturaFolhagem, Vetor(0.0f, 1.0f, 0.0f), true, Cor(0.0f, 0.5f, 0.0f), Cor(0.0f, 0.5f, 0.0f), Cor(0.0f, 0.5f, 0.0f), 10);
        
        bola = new Esfera(centroBola, raioBola, Cor(1.0f, 0.0f, 0.0f), Cor(1.0f, 0.0f, 0.0f), Cor(1.0f, 0.0f, 0.0f), 10);

        adicionarComponente(suporte);
        adicionarComponente(tronco);
        adicionarComponente(folhagem);
        adicionarComponente(bola);
    }
};

#endif