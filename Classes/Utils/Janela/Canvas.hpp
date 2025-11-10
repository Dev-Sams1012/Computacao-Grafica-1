#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <cmath>
#include <vector>
#include <string>
#include "Janela.hpp"
#include "../Ponto/Ponto.hpp"

using namespace std;

struct Canvas
{
    Janela janela;
    size_t nCol;
    size_t nLin;
    float Dx;
    float Dy;
    vector<vector<Cor>> imagem;

    Canvas(Janela j, size_t nlin, size_t ncol);

    void GeraImagem(string nomeArquivo);
};


#endif