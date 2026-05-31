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

    bool infinito;
    Ponto minPt;
    Ponto maxPt;

    bool temRaio;
    float raio;

    bool tem_textura;
    string arquivo_textura = "";
    unsigned char *textura = nullptr;
    float escala_textura;
    int tex_largura, tex_altura, tex_componentes;

    Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M);

    Plano(Ponto Ppi, Vetor nbar, string arquivoTextura, float escala_tex, int M);

    Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M, Ponto min, Ponto max);

    Plano(Ponto Ppi, Vetor nbar, string arquivoTextura, float escala_tex, int M, Ponto min, Ponto max);

    Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M, float r);

    Plano(Ponto Ppi, Vetor nbar, string arquivoTextura, float escala_tex, int M, float r);

    bool temTextura() const override { return tem_textura; }

    Cor texturaEm(const Ponto &p) const override;

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit) override;

    Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;

    string getNomeObj() const override { return "Plano"; }
};

#endif