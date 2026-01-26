#ifndef MALHA_HPP
#define MALHA_HPP

#include "../Triangulo/Triangulo.hpp"
#include "../ObjetoAbstrato/Objeto.hpp"

struct Malha : Objeto
{
    vector<Ponto> vertices;
    vector<Triangulo> faces;

    bool tem_textura;
    unsigned char* textura = nullptr;
    int tex_largura, tex_altura, tex_componentes;
    float escala_textura;

    Malha(vector<Ponto> v, vector<Triangulo> f, Cor Kd, Cor Ke, Cor Ka, int M);

    Malha(vector<Ponto> v, vector<Triangulo> f, string arquivoTextura, float escala, int M);

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit) override;

    Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;

    string getNomeObj() const override { return "Malha"; }
};

#endif