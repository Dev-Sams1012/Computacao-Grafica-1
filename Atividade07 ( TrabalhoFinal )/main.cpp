#define _USE_MATH_DEFINES

#include "../Classes/Utils/Janela/Janela.hpp"
#include "../Classes/Utils/Canvas/Canvas.hpp"
#include "../Classes/Utils/Camera/Camera.hpp"
#include "../Classes/Utils/InterfaceGrafica/interface.hpp"

#include "../Classes/Utils/Ponto/Ponto.hpp"
#include "../Classes/Utils/Vetor/Vetor.hpp"
#include "../Classes/Utils/Matriz/Matriz3x3.hpp"
#include "../Classes/Utils/Matriz/Matriz4x4.hpp"

#include "../Classes/Utils/Luz/LuzPontual/LuzPontual.hpp"
#include "../Classes/Utils/Luz/LuzSpot/LuzSpot.hpp"
#include "../Classes/Utils/Luz/LuzDirecional/LuzDirecional.hpp"

#include "../Classes/Objetos/Esfera/Esfera.hpp"
#include "../Classes/Objetos/Plano/Plano.hpp"
#include "../Classes/Objetos/Triangulo/Triangulo.hpp"
#include "../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../Classes/Objetos/Malha/Malha.hpp"
#include "../Classes/Objetos/Cone/Cone.hpp"
#include "../Classes/Objetos/Cubo/Cubo.hpp"
#include "../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"

#include "Objetos/poste.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Ponto origem = Ponto(0.0f, 0.0f, 0.0f);

    Janela janela = Janela(1.0f, 1.0f, 0.4f);

    size_t nCol = 600;
    size_t nLin = 600;

    Cor I_F = Cor(0.7f, 0.7f, 0.7f);
    Ponto P_F = Ponto(0.0f, 2.0f, 2.0f);
    Cor I_A = Cor(0.6f, 0.6f, 0.6f);

    LuzSpot luz = LuzSpot(P_F, Vetor(0.0f, 0.0f, -5.0f), 45.0f, I_F);
    LuzDirecional sol(Vetor(-0.3f, -0.4f, -0.2f), Cor(1.0f, 0.85f, 0.6f));

    Ponto pos_cam = Ponto(0.0f, 1.7f, 4.0f);

    Camera *camera = new Camera(pos_cam, Ponto(0.0f, 1.7f, -1.0f), Vetor(0.0f, 1.0f, 0.0f));

    Canvas *canvas = new Canvas(janela, nLin, nCol, camera, I_A);

    string pisoMadeira = "../Assets/madel-piso-vinilico-click-madeir.png";

    string ceu = "../Assets/textura-do-ceu_14223-97.png";

    Plano planoChao = Plano(Ponto(0.0f, 0.0f, 0.0f), Vetor(0.0f, 1.0f, 0.0f), pisoMadeira, 0.2f, 10);

    Plano planoCeu = Plano(Ponto(65.0f, -5.0f, -50.0f), Vetor(0.0f, 0.0f, 1.0f), ceu, 0.007f, 10);

    canvas->adicionaObjetoCena(&planoChao);
    canvas->adicionaObjetoCena(&planoCeu);

    canvas->adicionaObjetoCena(new Poste());

    //canvas->adicionaLuz(&luz);
    canvas->adicionaLuz(&sol);

    canvas->geraImagem("Imagem_Trabalho_Final");

    Interface::inicializar(argc, argv, nCol, nLin, canvas, "Trabalho Final - Computacao Grafica 1");

    glutMainLoop();

    return 0;
}