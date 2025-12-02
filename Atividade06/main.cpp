#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "../Classes/utils/Janela/Janela.hpp"
#include "../Classes/utils/Canvas/Canvas.hpp"
#include "../Classes/utils/Camera/Camera.hpp"
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
#include "ObjetosAtividade/Portico.hpp"
#include "ObjetosAtividade/Galpao.hpp"

using namespace std;

int main()
{
    Ponto origem = Ponto(0.0f, 0.0f, 0.0f);

    Janela janela = Janela(1.0f, 1.0f, 0.4f);

    size_t nCol = 600;
    size_t nLin = 600;

    Cor I_F = Cor(0.7f, 0.7f, 0.7f);
    Ponto P_F = Ponto(-1.0f, 1.4f, -0.2f);
    Cor I_A = Cor(0.3f, 0.3f, 0.3f);

    Luz luz = Luz(P_F, I_F, I_A);

    Ponto pos_cam = Ponto(0.0f, 0.0f, 0.0f);

    Camera* camera = new Camera(pos_cam, Ponto(0.0f, 0.0f, -1.0f), Vetor(0.0f, 1.0f, 0.0f));

    Canvas canvas = Canvas(janela, nLin, nCol, camera);

    string pisoMadeira = "../Assets/madel-piso-vinilico-click-madeir.png";

    string ceu = "../Assets/textura-do-ceu_14223-97.png";
    
    Plano planoChao = Plano(Ponto(0.0f, -2.0f, 0.0f), Vetor(0.0f, 1.0f, 0.0f), pisoMadeira, 0.2f, 10);

    Plano planoCeu = Plano(Ponto(-1000.0f, 0.0f, -50.0f), Vetor(0.0f, 0.0f, 1.0f), ceu, 0.01f, 1000);

    Mesa mesa = Mesa();

    ArvoreNatal arvore = ArvoreNatal();

    Galpao galpao = Galpao();

    canvas.adicionaObjetoCena(&planoChao);
    canvas.adicionaObjetoCena(&galpao);
    canvas.adicionaObjetoCena(&mesa);
    canvas.adicionaObjetoCena(&arvore);
    canvas.adicionaObjetoCena(&planoCeu);
    
    canvas.geraImagem(luz, "Imagem_Com_ObjetosComplexos");

    return 0;
}