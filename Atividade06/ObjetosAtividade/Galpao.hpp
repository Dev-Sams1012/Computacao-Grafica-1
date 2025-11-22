#ifndef GALPAO_HPP
#define GALPAO_HPP

#include "Portico.hpp"

struct Galpao : ObjetoComplexo
{
    Ponto centro;
    Portico *porticoFrontal;
    Portico *porticoTraseiro;
    Paralelepipedo *paredeEsq;
    Paralelepipedo *paredeDir;
    Paralelepipedo *paredeFundo;
    Paralelepipedo *painelTelhadoEsq;
    Paralelepipedo *painelTelhadoDir;

    Galpao()
    {
        porticoFrontal = new Portico();
        porticoTraseiro = new Portico();

        Matriz4x4 translacaoFrontal = Matriz4x4::translacao(0.0f, 0.0f, -5.0f);
        porticoFrontal->transforma(translacaoFrontal);

        Matriz4x4 translacaoTraseiro = Matriz4x4::translacao(0.0f, 0.0f, 5.0f);
        porticoTraseiro->transforma(translacaoTraseiro);

        float folga = 0.10f;

        float larguraParede = 0.2f;
        float alturaParede = porticoFrontal->colunaEsquerda->altura;
        float comprimentoParedeLat = 10.0f - (2.0f * folga);
        float comprimentoParedeFundo = 6.0f;

        float zFrontal = porticoFrontal->centroBase.Cord_z;
        float zTraseiro = porticoTraseiro->centroBase.Cord_z;
        float zParede = (zFrontal + zTraseiro) / 2.0f;

        float xParedeEsq = porticoFrontal->colunaEsquerda->centro.Cord_x + porticoFrontal->colunaEsquerda->largura / 2.0f - 0.10f;
        float xParedeDir = porticoFrontal->colunaDireita->centro.Cord_x - porticoFrontal->colunaDireita->largura / 2.0f + 0.10f;

        Ponto centroParedeEsq = Ponto(xParedeEsq, porticoFrontal->colunaEsquerda->centro.Cord_y, zParede);
        Ponto centroParedeDir = Ponto(xParedeDir, porticoFrontal->colunaDireita->centro.Cord_y, zParede);

        paredeEsq = new Paralelepipedo(larguraParede, comprimentoParedeLat, alturaParede, centroParedeEsq, Cor(0.6f, 0.6f, 0.6f), Cor(0.6f, 0.6f, 0.6f), Cor(0.6f, 0.6f, 0.6f), 10);

        paredeDir = new Paralelepipedo(larguraParede, comprimentoParedeLat, alturaParede, centroParedeDir, Cor(0.6f, 0.6f, 0.6f), Cor(0.6f, 0.6f, 0.6f), Cor(0.6f, 0.6f, 0.6f), 10);

        float alturaParedeFundo = alturaParede;

        float yBaseParedeFundo = porticoFrontal->centroBase.Cord_y - (alturaParede / 2.0f);

        float yCentroParedeFundo = yBaseParedeFundo + (alturaParedeFundo / 2.0f);

        Ponto centroParedeFundo = Ponto(0.0f, yCentroParedeFundo, zTraseiro - 4.84f);

        paredeFundo = new Paralelepipedo(comprimentoParedeFundo, larguraParede, alturaParede - 0.5, centroParedeFundo, Cor(0.6f, 0.6f, 0.6f), Cor(0.6f, 0.6f, 0.6f), Cor(0.6f, 0.6f, 0.6f), 10);

        Matriz4x4 desce = Matriz4x4::translacao(0.0f, -0.25f, 0.0f);

        paredeFundo->transforma(desce);

        float yTopoTelhado = porticoFrontal->colunaEsquerda->centro.Cord_y + (alturaParede / 2.0f);

        float zTelhado = zParede;

        float comprimentoTelhado = 10.0f;
        float larguraPainelTelhado = 3.0f;
        float espessuraTelhado = 0.1f;

        Ponto centroTelhadoEsq = Ponto(-1.5f, yTopoTelhado + 0.05f, zTelhado);
        Ponto centroTelhadoDir = Ponto(1.5f, yTopoTelhado + 0.05f, zTelhado);

        painelTelhadoEsq = new Paralelepipedo(larguraPainelTelhado, comprimentoTelhado, espessuraTelhado, centroTelhadoEsq, Cor(0.54f, 0.20f, 0.06f), Cor(0.54f, 0.20f, 0.06f), Cor(0.54f, 0.20f, 0.06f), 10);

        painelTelhadoDir = new Paralelepipedo(larguraPainelTelhado, comprimentoTelhado, espessuraTelhado, centroTelhadoDir, Cor(0.54f, 0.20f, 0.06f), Cor(0.54f, 0.20f, 0.06f), Cor(0.54f, 0.20f, 0.06f), 10);

        Matriz4x4 cisalhamentoEsquerda = Matriz4x4::cisalhaYX(0.75f);

        Matriz4x4 T1TelEsq = Matriz4x4::translacao(-centroTelhadoEsq.Cord_x, -centroTelhadoEsq.Cord_y, -centroTelhadoEsq.Cord_z);

        Matriz4x4 T2TelEsq = Matriz4x4::translacao(centroTelhadoEsq.Cord_x, centroTelhadoEsq.Cord_y, centroTelhadoEsq.Cord_z);

        Matriz4x4 subirTelhado = Matriz4x4::translacao(0.0f, 1.125f, 0.0f);

        Matriz4x4 transformaTelEsq = subirTelhado * T2TelEsq * cisalhamentoEsquerda * T1TelEsq;

        painelTelhadoEsq->transforma(transformaTelEsq);

        Matriz4x4 cisalhamentoDireita = Matriz4x4::cisalhaYX(-0.75f);

        Matriz4x4 T1TelDir = Matriz4x4::translacao(-centroTelhadoDir.Cord_x, -centroTelhadoDir.Cord_y, -centroTelhadoDir.Cord_z);

        Matriz4x4 T2TelDir = Matriz4x4::translacao(centroTelhadoDir.Cord_x, centroTelhadoDir.Cord_y, centroTelhadoDir.Cord_z);

        Matriz4x4 transformaTelDir = subirTelhado * T2TelDir * cisalhamentoDireita * T1TelDir;

        painelTelhadoDir->transforma(transformaTelDir);

        adicionarComponente(porticoFrontal);
        adicionarComponente(porticoTraseiro);
        adicionarComponente(paredeEsq);
        adicionarComponente(paredeDir);
        adicionarComponente(paredeFundo);
        adicionarComponente(painelTelhadoEsq);
        adicionarComponente(painelTelhadoDir);

        /*Ponto centroGalpao = Ponto(0.0f, paredeEsq->centro.Cord_y, paredeEsq->centro.Cord_z);

        Matriz4x4 T1 = Matriz4x4::translacao(-centroGalpao.Cord_x, -centroGalpao.Cord_y, -centroGalpao.Cord_z);

        Matriz4x4 R = Matriz4x4::rotacaoY(M_PI);

        Matriz4x4 T2 = Matriz4x4::translacao(centroGalpao.Cord_x, centroGalpao.Cord_y, centroGalpao.Cord_z);

        Matriz4x4 transformacaoCompleta = T2 * R * T1;

        this->transforma(transformacaoCompleta);*/
    }
};

#endif