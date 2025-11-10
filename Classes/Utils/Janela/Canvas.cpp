#include "Canvas.hpp"

Canvas::Canvas(Janela j, size_t nlin, size_t ncol){
    this->janela = j;
    this->nLin = nlin;
    this->nCol = ncol;
    Dx = janela.w / float(nCol);
    Dy = janela.h / float(nLin);
    imagem = vector<vector<Cor>>(nLin, vector<Cor>(nCol));
}

void Canvas::GeraImagem(string nomeArquivo){

}