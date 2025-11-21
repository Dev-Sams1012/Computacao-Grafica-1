#ifndef PORTICO_HPP
#define PORTICO_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "../../Classes/utils/Matriz/Matriz4x4.hpp"

struct Portico : ObjetoComplexo
{
    Paralelepipedo *colunaEsquerda;
    Paralelepipedo *colunaDireita;
    Paralelepipedo *vigaCisalhadaEsquerda;
    Paralelepipedo *vigaCisalhadaDireita;

    Portico()
    {
        float larguraColuna = 0.5f;
        float alturaColuna = 5.0f;
        float profundidadeColuna = 0.3f;

        float larguraViga = 3.0f;
        float alturaViga = 0.5f;
        float profundidadeViga = 0.3f;

        float yInferior = -1.5f;

        Ponto centroColunaEsquerda = Ponto(-3.0f, yInferior + alturaColuna / 2, -10.0f);
        Ponto centroColunaDireita = Ponto(3.5f, yInferior + alturaColuna / 2, -10.0f);

        Ponto centroVigaEsquerda = Ponto(centroColunaEsquerda.Cord_x + larguraColuna / 2 + larguraViga / 2, yInferior + alturaColuna - alturaViga / 2, centroColunaEsquerda.Cord_z);

        Ponto centroVigaDireita = Ponto(centroColunaDireita.Cord_x - larguraColuna / 2 - larguraViga / 2, yInferior + alturaColuna - alturaViga / 2, centroColunaDireita.Cord_z);

        colunaEsquerda = new Paralelepipedo(larguraColuna, profundidadeColuna, alturaColuna, centroColunaEsquerda, Cor(0.7f, 0.7f, 0.7f), Cor(0.7f, 0.7f, 0.7f), Cor(0.7f, 0.7f, 0.7f), 10);

        colunaDireita = new Paralelepipedo(larguraColuna, profundidadeColuna, alturaColuna, centroColunaDireita, Cor(0.7f, 0.7f, 0.7f), Cor(0.7f, 0.7f, 0.7f), Cor(0.7f, 0.7f, 0.7f), 10);

        vigaCisalhadaEsquerda = new Paralelepipedo(larguraViga, profundidadeViga, alturaViga, centroVigaEsquerda, Cor(0.5f, 0.5f, 0.5f), Cor(0.5f, 0.5f, 0.5f), Cor(0.5f, 0.5f, 0.5f), 10);

        Matriz4x4 cisalhamentoEsquerda = Matriz4x4::cisalhaYX(0.75f);

        Matriz4x4 T1VigaEsq = Matriz4x4::translacao(-centroVigaEsquerda.Cord_x, -centroVigaEsquerda.Cord_y, -centroVigaEsquerda.Cord_z);

        Matriz4x4 T2VigaEsq = Matriz4x4::translacao(centroVigaEsquerda.Cord_x, centroVigaEsquerda.Cord_y, centroVigaEsquerda.Cord_z);

        Matriz4x4 subirViga = Matriz4x4::translacao(0.0f, 1.125f, 0.0f);

        Matriz4x4 transformaVigaEsq = subirViga * T2VigaEsq * cisalhamentoEsquerda * T1VigaEsq;

        vigaCisalhadaEsquerda->transforma(transformaVigaEsq);

        vigaCisalhadaDireita = new Paralelepipedo(larguraViga, profundidadeViga, alturaViga, centroVigaDireita, Cor(0.5f, 0.5f, 0.5f), Cor(0.5f, 0.5f, 0.5f), Cor(0.5f, 0.5f, 0.5f), 10);

        Matriz4x4 cisalhamentoDireita = Matriz4x4::cisalhaYX(-0.75f);

        Matriz4x4 T1VigaDir = Matriz4x4::translacao(-centroVigaDireita.Cord_x, -centroVigaDireita.Cord_y, -centroVigaDireita.Cord_z);

        Matriz4x4 T2VigaDir = Matriz4x4::translacao(centroVigaDireita.Cord_x, centroVigaDireita.Cord_y, centroVigaDireita.Cord_z);

        Matriz4x4 transformaVigaDir = subirViga * T2VigaDir * cisalhamentoDireita * T1VigaDir;

        vigaCisalhadaDireita->transforma(transformaVigaDir);

        adicionarComponente(colunaEsquerda);
        adicionarComponente(colunaDireita);
        adicionarComponente(vigaCisalhadaEsquerda);
        adicionarComponente(vigaCisalhadaDireita);
    }
};

#endif