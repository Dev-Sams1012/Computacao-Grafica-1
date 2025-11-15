#ifndef PLANO_HPP
#define PLANO_HPP

#include "../BibliotecasExternas/stb_image.hpp"
#include "../ObjetoAbstrato/Objeto.hpp"

#include <string>
#include <iostream>

struct Plano : public Objeto
{
    Ponto P_pi;
    Vetor n_bar;
    bool tem_textura;
    string arquivo_textura = "";
    unsigned char* textura = nullptr;
    int tex_largura, tex_altura, tex_componentes;

    Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M);

    Plano(Ponto Ppi, Vetor nbar, string arquivoTextura, int M);

    Cor texturaEm(Ponto p);

    bool raioIntercepta(Ponto origem, Ponto canvas) override;

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override;
};

#endif