#ifndef POSTE_HPP
#define POSTE_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "../../Classes/Objetos/Cubo/Cubo.hpp"

struct Poste : ObjetoComplexo
{
    Paralelepipedo *base;
    Cilindro *suporte;
    Cilindro *hasteEsq;
    Cilindro *hasteDir;
    Paralelepipedo *luminariaEsq;
    Paralelepipedo *luminariaDir;

    Poste()
    {
        float ladosBase = 0.3f;
        float alturaBase = 0.05f;

        Ponto centroideBase = Ponto(0.0f, alturaBase / 2, 0.0f);

        base = new Paralelepipedo(ladosBase, ladosBase, alturaBase, centroideBase, Cor(0.2f, 0.2f, 0.2f), Cor(0.2f, 0.2f, 0.2f), Cor(0.2f, 0.2f, 0.2f), 10);

        float raioSuporte = 0.05f;
        float alturaSuporte = 3.0f;

        Ponto posSuporte = Ponto(0.0f, alturaBase, 0.0f);
        Vetor dirSuporte = Vetor(0.0f, 1.0f, 0.0f);

        suporte = new Cilindro(posSuporte, raioSuporte, alturaSuporte, dirSuporte, true, true, Cor(0.2f, 0.2f, 0.2f), Cor(0.2f, 0.2f, 0.2f), Cor(0.2f, 0.2f, 0.2f), 10);

        Ponto posHasteEsq = Ponto(-0.048f, alturaBase / 2 + alturaSuporte - 0.15f, 0.0f);
        Ponto posHasteDir = Ponto(0.048f, alturaBase / 2 + alturaSuporte - 0.15f, 0.0f);

        float raioHaste = 0.02f;
        float alturaHaste = 0.2f;

        Vetor dirHasteEsq = Vetor(-1.0f, 0.0f, 0.0f);
        Vetor dirHasteDir = Vetor(1.0f, 0.0f, 0.0f);

        hasteEsq = new Cilindro(posHasteEsq, raioHaste, alturaHaste, dirHasteEsq, true, true, Cor(0.2f, 0.2f, 0.2f), Cor(0.2f, 0.2f, 0.2f), Cor(0.2f, 0.2f, 0.2f), 10);

        hasteDir = new Cilindro(posHasteDir, raioHaste, alturaHaste, dirHasteDir, true, true, Cor(0.2f, 0.2f, 0.2f), Cor(0.2f, 0.2f, 0.2f), Cor(0.2f, 0.2f, 0.2f), 10);

        float ang = 0.34f;

        Ponto pEsq = posHasteEsq;
        Ponto pDir = posHasteDir;

        Matriz4x4 T1e = Matriz4x4::translacao(-pEsq.Cord_x, -pEsq.Cord_y, -pEsq.Cord_z);
        Matriz4x4 Re = Matriz4x4::rotacaoZ(-ang);
        Matriz4x4 T2e = Matriz4x4::translacao(pEsq.Cord_x, pEsq.Cord_y, pEsq.Cord_z);
        hasteEsq->transforma(T2e * Re * T1e);

        Matriz4x4 T1d = Matriz4x4::translacao(-pDir.Cord_x, -pDir.Cord_y, -pDir.Cord_z);
        Matriz4x4 Rd = Matriz4x4::rotacaoZ(ang);
        Matriz4x4 T2d = Matriz4x4::translacao(pDir.Cord_x, pDir.Cord_y, pDir.Cord_z);
        hasteDir->transforma(T2d * Rd * T1d);

        float tamanhoLuminaria = 0.30f;
        float alturaLuminaria = 0.05f;

        Ponto fimHasteEsq = ray(posHasteEsq, dirHasteEsq, alturaHaste);
        Ponto fimHasteDir = ray(posHasteDir, dirHasteDir, alturaHaste);

        Ponto posLumEsq = ray(fimHasteEsq, dirHasteEsq, tamanhoLuminaria / 2.0f);
        Ponto posLumDir = ray(fimHasteDir, dirHasteDir, tamanhoLuminaria / 2.0f);

        luminariaEsq = new Paralelepipedo(
            tamanhoLuminaria, tamanhoLuminaria, alturaLuminaria,
            posLumEsq,
            Cor(1.0f, 1.0f, 0.8f),
            Cor(1.0f, 1.0f, 0.8f),
            Cor(1.0f, 1.0f, 0.8f),
            10);

        luminariaDir = new Paralelepipedo(
            tamanhoLuminaria, tamanhoLuminaria, alturaLuminaria,
            posLumDir,
            Cor(1.0f, 1.0f, 0.8f),
            Cor(1.0f, 1.0f, 0.8f),
            Cor(1.0f, 1.0f, 0.8f),
            10);

        luminariaEsq->transforma(T2e * Re * T1e);

        luminariaDir->transforma(T2d * Rd * T1d);

        adicionarComponente(base);
        adicionarComponente(suporte);
        adicionarComponente(hasteEsq);
        adicionarComponente(hasteDir);
        adicionarComponente(luminariaEsq);
        adicionarComponente(luminariaDir);
    }
};

#endif