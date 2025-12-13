#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include "../Janela/Janela.hpp"
#include "../Luz/Luz.hpp"
#include "../Ponto/Ponto.hpp"
#include "../Vetor/Vetor.hpp"
#include "../Camera/Camera.hpp"
#include "../../Objetos/ObjetoAbstrato/Objeto.hpp"

using namespace std;

struct Canvas
{
    Camera* camera;
    Janela janela;
    size_t nCol;
    size_t nLin;
    float Dx;
    float Dy;
    vector<vector<Cor>> imagem;
    vector<Objeto *> objetos;
    vector<Luz*> luzes;

    Canvas(Janela j, size_t nlin, size_t ncol, Camera* cam);

    void adicionaObjetoCena(Objeto *obj);

    void adicionaLuz(Luz *luz);

    void geraImagem(Luz luz, string nomeArquivo);
};

#endif