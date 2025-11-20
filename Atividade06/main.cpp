#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "../Classes/utils/Janela/Janela.hpp"
#include "../Classes/utils/Janela/Canvas.hpp"
#include "../Classes/utils/Ponto/Ponto.hpp"
#include "../Classes/utils/Vetor/Vetor.hpp"
#include "../Classes/utils/Matriz/Matriz3x3.hpp"
#include "../Classes/utils/Matriz/Matriz4x4.hpp"

#include "../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../Classes/Objetos/Malha/Malha.hpp"
#include "../Classes/Objetos/Triangulo/Triangulo.hpp"
#include "../Classes/Objetos/Cone/Cone.hpp"
#include "../Classes/Objetos/Esfera/Esfera.hpp"
#include "../Classes/Objetos/Plano/Plano.hpp"
#include "../Classes/Objetos/Cubo/Cubo.hpp"
#include "../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "ObjetosAtividade/Mesa.hpp"
#include "ObjetosAtividade/ArvoreNatal.hpp"

using namespace std;

int main()
{
    /* origem do Observador */
    Ponto origem = Ponto(0.0f, 0.0f, 0.0f);

    /* janela Real */
    Janela janela = Janela(0.6f, 0.6f, 0.3f);

    size_t nCol = 600;
    size_t nLin = 600;

    Cor I_F = Cor(0.7f, 0.7f, 0.7f);
    Ponto P_F = Ponto(-1.0f, 1.4f, -0.2f);
    Cor I_A = Cor(0.3f, 0.3f, 0.3f);

    Luz luz = Luz(P_F, I_F, I_A);

    Canvas canvas = Canvas(janela, nLin, nCol, origem);

    string pisoMadeira = "../Assets/madel-piso-vinilico-click-madeir.png";

    Plano planoChao = Plano(Ponto(0.0f, -1.5f, 0.0f), Vetor(0.0f, 1.0f, 0.0f), pisoMadeira, 10);



    ArvoreNatal arvoreNatal = ArvoreNatal();

    canvas.adicionaObjetoCena(&planoChao);

    canvas.adicionaObjetoCena(&arvoreNatal);

    canvas.geraImagem(luz, "Imagem_Com_ObjetosComplexos");

    return 0;
}