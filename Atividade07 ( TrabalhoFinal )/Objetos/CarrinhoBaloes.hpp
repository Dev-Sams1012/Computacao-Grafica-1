#ifndef CARRINHO_BALOES_HPP
#define CARRINHO_BALOES_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../../Classes/Objetos/Elipsoide/Elipsoide.hpp"
#include "../../Classes/Utils/Matriz/Matriz4x4.hpp"

struct CarrinhoBaloes : ObjetoComplexo
{
    Paralelepipedo *corpo;
    Paralelepipedo *tampo;

    Cilindro *aroEsquerdo, *aroDireito;
    Cilindro *cuboEsquerdo, *cuboDireito;
    Cilindro *raiosEsquerdo[8], *raiosDireito[8];

    Cilindro *apoioTraseiroE, *apoioTraseiroD;
    Cilindro *hasteEsquerda, *hasteDireita, *barraConducao;

    Cilindro *cordaoBalaoR, *cordaoBalaoG, *cordaoBalaoB;
    Elipsoide *balaoVermelho, *balaoVerde, *balaoAzul;

    CarrinhoBaloes()
    {
        Cor corVermelho(0.8f, 0.1f, 0.1f);
        Cor corVerde(0.1f, 0.7f, 0.1f);
        Cor corAzul(0.1f, 0.1f, 0.8f);
        Cor corMetal(0.4f, 0.4f, 0.4f);
        Cor corPreto(0.05f, 0.05f, 0.05f);
        Cor corBranco(0.9f, 0.9f, 0.9f);
        Cor corMadeira(0.9f, 0.8f, 0.6f);

        float corpoLargura = 0.6f, corpoAltura = 0.5f, corpoProfundidade = 0.8f;
        float alturaVaoLivre = 0.25f, espessuraTampo = 0.04f;
        float rodaRaio = 0.22f, rodaLargura = 0.06f, cuboRaio = 0.03f;
        float balaoRaioXZ = 0.16f, balaoRaioY = 0.21f, cordaoComprimento = 1.1f;

        Ponto posCorpo(0.0f, alturaVaoLivre + (corpoAltura / 2.0f), 0.0f);
        corpo = new Paralelepipedo(corpoLargura, corpoProfundidade, corpoAltura, posCorpo, corVermelho, corVermelho, corVermelho, 10);
        adicionarComponente(corpo);

        Ponto posTampo(0.0f, alturaVaoLivre + corpoAltura + (espessuraTampo / 2.0f), 0.0f);
        tampo = new Paralelepipedo(corpoLargura + 0.1f, corpoProfundidade + 0.1f, espessuraTampo, posTampo, corMadeira, corMadeira, corMadeira, 10);
        adicionarComponente(tampo);

        float offsetEixoX = corpoLargura / 2.0f + 0.04f;
        float posicaoEixoZ = -corpoProfundidade / 3.0f;
        Vetor direcaoEixo(1.0f, 0.0f, 0.0f);

        Ponto centroRodaEsq(-offsetEixoX, rodaRaio, posicaoEixoZ);
        Ponto baseCilindroEsq(centroRodaEsq.Cord_x - (rodaLargura / 2.0f), centroRodaEsq.Cord_y, centroRodaEsq.Cord_z);

        aroEsquerdo = new Cilindro(baseCilindroEsq, rodaRaio, rodaRaio - 0.02f, rodaLargura, direcaoEixo, true, true, true, corPreto, corPreto, corPreto, 10);
        cuboEsquerdo = new Cilindro(baseCilindroEsq, cuboRaio, 0.0f, rodaLargura, direcaoEixo, true, true, false, corMetal, corMetal, corMetal, 10);
        adicionarComponente(aroEsquerdo);
        adicionarComponente(cuboEsquerdo);

        for (int i = 0; i < 8; i++)
        {
            float angulo = i * (M_PI / 4.0f);

            Vetor dirRaio(0.0f, cos(angulo), sin(angulo));
            Ponto posInicial(centroRodaEsq.Cord_x, centroRodaEsq.Cord_y + dirRaio.Cord_y * cuboRaio, centroRodaEsq.Cord_z + dirRaio.Cord_z * cuboRaio);

            raiosEsquerdo[i] = new Cilindro(posInicial, 0.008f, rodaRaio - cuboRaio - 0.01f, dirRaio, true, true, corMetal, corMetal, corMetal, 10);

            adicionarComponente(raiosEsquerdo[i]);
        }

        Ponto centroRodaDir(offsetEixoX, rodaRaio, posicaoEixoZ);
        Ponto baseCilindroDir(centroRodaDir.Cord_x - (rodaLargura / 2.0f), centroRodaDir.Cord_y, centroRodaDir.Cord_z);

        aroDireito = new Cilindro(baseCilindroDir, rodaRaio, rodaRaio - 0.02f, rodaLargura, direcaoEixo, true, true, true, corPreto, corPreto, corPreto, 10);
        cuboDireito = new Cilindro(baseCilindroDir, cuboRaio, 0.0f, rodaLargura, direcaoEixo, true, true, false, corMetal, corMetal, corMetal, 10);
        adicionarComponente(aroDireito);
        adicionarComponente(cuboDireito);

        for (int i = 0; i < 8; i++)
        {
            float angulo = i * (M_PI / 4.0f);

            Vetor dirRaio(0.0f, cos(angulo), sin(angulo));
            Ponto posInicial(centroRodaDir.Cord_x, centroRodaDir.Cord_y + dirRaio.Cord_y * cuboRaio, centroRodaDir.Cord_z + dirRaio.Cord_z * cuboRaio);

            raiosDireito[i] = new Cilindro(posInicial, 0.008f, rodaRaio - cuboRaio - 0.01f, dirRaio, true, true, corMetal, corMetal, corMetal, 10);

            adicionarComponente(raiosDireito[i]);
        }

        float posicaoApoioZ = corpoProfundidade / 2.0f - 0.1f;

        apoioTraseiroE = new Cilindro(Ponto(-corpoLargura / 4.0f, 0.0f, posicaoApoioZ), 0.025f, alturaVaoLivre, Vetor(0, 1, 0), true, true, corMetal, corMetal, corMetal, 10);
        apoioTraseiroD = new Cilindro(Ponto(corpoLargura / 4.0f, 0.0f, posicaoApoioZ), 0.025f, alturaVaoLivre, Vetor(0, 1, 0), true, true, corMetal, corMetal, corMetal, 10);

        adicionarComponente(apoioTraseiroE);
        adicionarComponente(apoioTraseiroD);

        Vetor direcaoHaste(0.0f, cos(0.7f), sin(0.7f));
        float comprimentoHaste = 0.45f;

        Ponto baseHasteE(-corpoLargura / 2.0f, alturaVaoLivre + corpoAltura, corpoProfundidade / 2.0f);
        Ponto baseHasteD(corpoLargura / 2.0f, alturaVaoLivre + corpoAltura, corpoProfundidade / 2.0f);

        hasteEsquerda = new Cilindro(baseHasteE, 0.015f, comprimentoHaste, direcaoHaste, true, true, corMetal, corMetal, corMetal, 10);
        hasteDireita = new Cilindro(baseHasteD, 0.015f, comprimentoHaste, direcaoHaste, true, true, corMetal, corMetal, corMetal, 10);

        Ponto fimHasteE(baseHasteE.Cord_x, baseHasteE.Cord_y + direcaoHaste.Cord_y * comprimentoHaste, baseHasteE.Cord_z + direcaoHaste.Cord_z * comprimentoHaste);

        barraConducao = new Cilindro(Ponto(fimHasteE.Cord_x - 0.05f, fimHasteE.Cord_y, fimHasteE.Cord_z), 0.025f, corpoLargura + 0.1f, Vetor(1, 0, 0), true, true, corPreto, corPreto, corPreto, 10);

        adicionarComponente(hasteEsquerda);
        adicionarComponente(hasteDireita);
        adicionarComponente(barraConducao);

        Ponto posicaoFixacaoBaloes(0.0f, alturaVaoLivre + corpoAltura + espessuraTampo, -corpoProfundidade / 2.0f + 0.1f);
        float deslocamentoBalao = cordaoComprimento + balaoRaioY;

        Vetor dirR = normalizar(Vetor(-0.2f, 0.95f, 0.1f));

        cordaoBalaoR = new Cilindro(posicaoFixacaoBaloes, 0.004f, cordaoComprimento, dirR, true, true, corBranco, corBranco, corBranco, 10);

        balaoVermelho = new Elipsoide(Ponto(0, 0, 0), balaoRaioXZ, balaoRaioY, balaoRaioXZ, corVermelho, corVermelho, corVermelho, 50);

        Ponto centroR = ray(posicaoFixacaoBaloes, dirR, deslocamentoBalao);

        balaoVermelho->transforma(Matriz4x4::translacao(centroR.Cord_x, centroR.Cord_y, centroR.Cord_z));

        adicionarComponente(cordaoBalaoR);
        adicionarComponente(balaoVermelho);

        Vetor dirG = normalizar(Vetor(0.0f, 1.0f, 0.0f));

        cordaoBalaoG = new Cilindro(posicaoFixacaoBaloes, 0.004f, cordaoComprimento, dirG, true, true, corBranco, corBranco, corBranco, 10);

        balaoVerde = new Elipsoide(Ponto(0, 0, 0), balaoRaioXZ, balaoRaioY, balaoRaioXZ, corVerde, corVerde, corVerde, 50);

        Ponto centroG = ray(posicaoFixacaoBaloes, dirG, deslocamentoBalao);

        balaoVerde->transforma(Matriz4x4::translacao(centroG.Cord_x, centroG.Cord_y, centroG.Cord_z));

        adicionarComponente(cordaoBalaoG);
        adicionarComponente(balaoVerde);

        Vetor dirB = normalizar(Vetor(0.2f, 0.95f, -0.1f));

        cordaoBalaoB = new Cilindro(posicaoFixacaoBaloes, 0.004f, cordaoComprimento, dirB, true, true, corBranco, corBranco, corBranco, 10);

        balaoAzul = new Elipsoide(Ponto(0, 0, 0), balaoRaioXZ, balaoRaioY, balaoRaioXZ, corAzul, corAzul, corAzul, 50);

        Ponto centroB = ray(posicaoFixacaoBaloes, dirB, deslocamentoBalao);

        balaoAzul->transforma(Matriz4x4::translacao(centroB.Cord_x, centroB.Cord_y, centroB.Cord_z));

        adicionarComponente(cordaoBalaoB);
        adicionarComponente(balaoAzul);
    }
};

#endif