#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "../../../BibliotecasExternas/stb_image.hpp"
#include "../ObjetoAbstrato/Objeto.hpp"

struct Triangulo : Objeto
{
    Ponto p0;
    Ponto p1;
    Ponto p2;
    Vetor normal;

    bool tem_textura;
    string arquivo_textura = "";
    unsigned char *textura = nullptr;
    float escala_textura;
    int tex_largura, tex_altura, tex_componentes;

    Triangulo(Ponto p1, Ponto p2, Ponto p0, Cor Kd, Cor Ke, Cor Ka, int M);

    Triangulo(Ponto p1, Ponto p2, Ponto p0, unsigned char *texPronta, int largura, int altura, float escala, int M);

    void atualizarNormal();

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit) override;

    Vetor normalEm(const Ponto &P) const override;

    bool temTextura() const override { return tem_textura; }

    Cor texturaEm(const Ponto &p) const override;

    void transforma(const Matriz4x4 &M) override;

    string getNomeObj() const override { return "Triangulo"; }
};

#endif