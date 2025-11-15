#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "../Classes/utils/Janela/Janela.hpp"
#include "../Classes/utils/Janela/Canvas.hpp"
#include "../Classes/utils/ponto/Ponto.hpp"
#include "../Classes/utils/Vetor/Vetor.hpp"
#include "../Classes/utils/Matriz3x3/Matriz3x3.hpp"

#include "../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../Classes/Objetos/Malha/Malha.hpp"
#include "../Classes/Objetos/Triangulo/Triangulo.hpp"
#include "../Classes/Objetos/Cone/Cone.hpp"
#include "../Classes/Objetos/Esfera/Esfera.hpp"
#include "../Classes/Objetos/Plano/Plano.hpp"
#include "../Classes/Objetos/Cubo/Cubo.hpp"

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

    Plano planoLateralDireita = Plano(Ponto(2.0f, -1.5f, 0.0f), Vetor(-1.0f, 0.0f, 0.0f), Cor(0.686f, 0.933f, 0.933f), Cor(0.686f, 0.933f, 0.933f), Cor(0.686f, 0.933f, 0.933f), 10);

    Plano planoLateralEsquerda = Plano(Ponto(-2.0f, -1.5f, 0.0f), Vetor(1.0f, 0.0f, 0.0f), Cor(0.686f, 0.933f, 0.933f), Cor(0.686f, 0.933f, 0.933f), Cor(0.686f, 0.933f, 0.933f), 10);

    Plano planoFrontal = Plano(Ponto(2.0f, -1.5f, -4.0f), Vetor(0.0f, 0.0f, 1.0f), Cor(0.686f, 0.933f, 0.933f), Cor(0.686f, 0.933f, 0.933f), Cor(0.686f, 0.933f, 0.933f), 10);

    Plano planoTeto = Plano(Ponto(0.0f, 1.5f, 0.0f), Vetor(0.0f, -1.0f, 0.0f), Cor(0.686f, 0.933f, 0.933f), Cor(0.686f, 0.933f, 0.933f), Cor(0.933f, 0.933f, 0.933f), 10);

    Cilindro cilindro = Cilindro(Ponto(0.0, -1.5, -2.0), 0.05f, 0.9f, Vetor(0.0f, 1.0f, 0.0f), Cor(0.824f, 0.706f, 0.549f), Cor(0.824f, 0.706f, 0.549f), Cor(0.824f, 0.706f, 0.549f), 10);

    Cone cone = Cone(Ponto(0.0f, -0.6, -2.0), 0.9f, 1.5f, Vetor(0.0f, 1.0f, 0.0f), Cor(0.0f, 1.0f, 0.498f), Cor(0.0f, 1.0f, 0.498f), Cor(0.0f, 1.0f, 0.498f), 10);

    Esfera esfera = Esfera(Ponto(0.0f, 0.95f, -2.0f), 0.05f, Cor(0.854f, 0.647f, 0.125f), Cor(0.854f, 0.647f, 0.125f), Cor(0.854f, 0.647f, 0.125f), 10);

    double aresta = 0.4;
    Ponto cbase = Ponto(0.0f , -1.5f , -1.65f);

    Cubo cubo = Cubo(aresta, cbase, Cor(1.0f, 0.078f, 0.576f), Cor(1.0f, 0.078f, 0.576f), Cor(1.0f, 0.078f, 0.576f), 1);

    canvas.adicionaObjetoCena(&planoChao);
    canvas.adicionaObjetoCena(&planoLateralDireita);
    canvas.adicionaObjetoCena(&planoLateralEsquerda);
    canvas.adicionaObjetoCena(&planoFrontal);
    canvas.adicionaObjetoCena(&planoTeto);
    canvas.adicionaObjetoCena(&cilindro);
    canvas.adicionaObjetoCena(&cone);
    canvas.adicionaObjetoCena(&esfera);
    canvas.adicionaObjetoCena(&cubo);

    canvas.geraImagem(luz, "Imagem_Com_Malha");

    return 0;
}