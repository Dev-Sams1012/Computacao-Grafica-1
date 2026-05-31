#ifndef FONTE_HPP
#define FONTE_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../../Classes/Objetos/Esfera/Esfera.hpp"
#include "../../Classes/Objetos/Plano/Plano.hpp"
#include "../../Classes/Utils/Matriz/Matriz4x4.hpp"

struct Fonte : ObjetoComplexo
{
    Fonte()
    {
        // --- MATERIAIS ---
        Cor pedraKd(0.4f, 0.4f, 0.45f), pedraKe(0.2f, 0.2f, 0.2f), pedraKa(0.1f, 0.1f, 0.15f);
        Cor aguaKd(0.1f, 0.4f, 0.6f), aguaKe(0.9f, 0.9f, 1.0f), aguaKa(0.1f, 0.1f, 0.2f);
        string texAgua = "../Assets/textura_agua.png";

        Vetor up(0, 1, 0);
        float m_pedra = 30;

        // 1. HASTE CENTRAL
        float hHaste = 2.4f;
        float rHaste = 0.12f;
        Cilindro *haste = new Cilindro(Ponto(0, 0, 0), rHaste, hHaste, up, true, true, pedraKd, pedraKe, pedraKa, m_pedra);
        adicionarComponente(haste);

        // 2. NÍVEL 1: BASE GRANDE (Aro + Chão + Água)
        float rBase = 1.8f;
        float hBase = 0.4f;
        float rIntBase = rBase - 0.12f;

        // Parede lateral (Aro oco)
        Cilindro *aroBase = new Cilindro(Ponto(0, 0, 0), rBase, rIntBase, hBase, up, false, false, pedraKd, pedraKe, pedraKa, m_pedra);
        adicionarComponente(aroBase);
        // Chão da base (Fundo)
        Plano *fundoBase = new Plano(Ponto(0, 0, 0), up, pedraKd, pedraKe, pedraKa, m_pedra, rBase);
        adicionarComponente(fundoBase);
        // Água da base (Na metade da altura do aro)
        Plano *aguaBase = new Plano(Ponto(0, hBase * 0.5f, 0), up, texAgua, 0.33f, 100, rIntBase);
        adicionarComponente(aguaBase);

        // 3. NÍVEL 2: BACIA MÉDIA (Semiesfera + Água no meio)
        float yMedia = 1.1f;
        float rMedia = 1.0f;
        // Bacia (InverterCorte = true para ser tigela/U)
        Esfera *baciaMedia = new Esfera(Ponto(0, yMedia, 0), rMedia, pedraKd, pedraKe, pedraKa, m_pedra, true, true);
        adicionarComponente(baciaMedia);
        // Água da Bacia Média (Posicionada na metade da profundidade da semiesfera)
        // O centro da esfera está em yMedia, então a água fica um pouco abaixo dele
        Plano *aguaMedia = new Plano(Ponto(0, yMedia - (rMedia * 0.4f), 0), up, texAgua, 0.33f, 100, rMedia * 0.9f);
        adicionarComponente(aguaMedia);

        // 4. NÍVEL 3: BACIA PEQUENA (Topo)
        float yTopo = 1.9f;
        float rTopo = 0.6f;
        Esfera *baciaTopo = new Esfera(Ponto(0, yTopo, 0), rTopo, pedraKd, pedraKe, pedraKa, m_pedra, true, true);
        adicionarComponente(baciaTopo);
        // Água da Bacia Topo (Também na metade da profundidade)
        Plano *aguaTopo = new Plano(Ponto(0, yTopo - (rTopo * 0.4f), 0), up, texAgua, 0.33f, 100, rTopo * 0.9f);
        adicionarComponente(aguaTopo);

        // 5. BORDAS DE ARO NAS BACIAS
        // Borda para a bacia média
        Cilindro *aroBordaMed = new Cilindro(Ponto(0, yMedia, 0), rMedia + 0.05f, rMedia - 0.05f, 0.1f, up, false, false, pedraKd, pedraKe, pedraKa, m_pedra);
        adicionarComponente(aroBordaMed);
        // Borda para a bacia topo
        Cilindro *aroBordaTop = new Cilindro(Ponto(0, yTopo, 0), rTopo + 0.05f, rTopo - 0.05f, 0.1f, up, false, false, pedraKd, pedraKe, pedraKa, m_pedra);
        adicionarComponente(aroBordaTop);
    }
};

#endif