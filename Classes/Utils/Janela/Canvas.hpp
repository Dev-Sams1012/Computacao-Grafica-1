#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include "Janela.hpp"
#include "Luz.hpp"
#include "../Ponto/Ponto.hpp"
#include "../Vetor/Vetor.hpp"
#include "../../Objetos/ObjetoAbstrato/Objeto.hpp"

using namespace std;

struct Canvas
{
    Ponto origem;
    Janela janela;
    size_t nCol;
    size_t nLin;
    float Dx;
    float Dy;
    vector<vector<Cor>> imagem;
    vector<Objeto *> objetos;

    Canvas(Janela j, size_t nlin, size_t ncol, Ponto origem = Ponto(0.0, 0.0, 0.0));

    void adicionaObjetoCena(Objeto *obj);

    bool temSombra(Ponto P_I, Luz luz, Objeto *objeto_atual);

    void geraImagem(Luz luz, string nomeArquivo);
};

#endif