#ifndef PLANO_HPP
#define PLANO_HPP

#include "../../../BibliotecasExternas/stb_image.hpp"
#include "../ObjetoAbstrato/Objeto.hpp"

#include <string>
#include <iostream>

struct Plano : public Objeto
{
    Ponto P_pi;
    Vetor n_bar;
    bool tem_textura;
    string arquivo_textura = "";
    unsigned char *textura = nullptr;
    float escala_textura;
    int tex_largura, tex_altura, tex_componentes;

    Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M);

    Plano(Ponto Ppi, Vetor nbar, string arquivoTextura, float escala_tex, int M);

    bool temTextura() const override { return tem_textura; }

    Cor texturaEm(const Ponto &p) const override;

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr) override;

    Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;
};

#endif