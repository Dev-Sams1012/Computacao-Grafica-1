#define _USE_MATH_DEFINES

#include "../Classes/Utils/Camera/Camera.hpp"
#include "../Classes/Utils/Canvas/Canvas.hpp"
#include "../Classes/Utils/InterfaceGrafica/interface.hpp"
#include "../Classes/Utils/Janela/Janela.hpp"

#include "../Classes/Utils/Matriz/Matriz3x3.hpp"
#include "../Classes/Utils/Matriz/Matriz4x4.hpp"
#include "../Classes/Utils/Ponto/Ponto.hpp"
#include "../Classes/Utils/Vetor/Vetor.hpp"

#include "../Classes/Utils/Luz/LuzDirecional/LuzDirecional.hpp"
#include "../Classes/Utils/Luz/LuzPontual/LuzPontual.hpp"
#include "../Classes/Utils/Luz/LuzSpot/LuzSpot.hpp"

#include "../Classes/Objetos/Cilindro/Cilindro.hpp"
#include "../Classes/Objetos/Cone/Cone.hpp"
#include "../Classes/Objetos/Cubo/Cubo.hpp"
#include "../Classes/Objetos/Elipsoide/Elipsoide.hpp"
#include "../Classes/Objetos/Esfera/Esfera.hpp"
#include "../Classes/Objetos/Malha/Malha.hpp"
#include "../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"
#include "../Classes/Objetos/Plano/Plano.hpp"
#include "../Classes/Objetos/Triangulo/Triangulo.hpp"

#include "Objetos/Arvore.hpp"
#include "Objetos/Banco.hpp"
#include "Objetos/Banqueta.hpp"
#include "Objetos/CarrinhoBaloes.hpp"
#include "Objetos/Fonte.hpp"
#include "Objetos/Lixeira.hpp"
#include "Objetos/Mesa.hpp"
#include "Objetos/Poste.hpp"
#include "Objetos/Tabuleiro.hpp"

using namespace std;

int main(int argc, char **argv)
{
    // =========================================================
    // 1. Janela e Canvas
    // =========================================================
    Janela janela(0.5f, 0.7f, 1.0f); // Fundo azul céu
    size_t largura = 800, altura = 800;
    Cor luzAmbiente(0.35f, 0.35f, 0.4f);

    // =========================================================
    // 2. Iluminação (Sol posicionado para iluminar a quina do L)
    // =========================================================
    Vetor dirSol = normalizar(Vetor(-1.0f, -1.5f, -1.0f));
    LuzDirecional sol(dirSol, Cor(1.0f, 0.98f, 0.9f));

    // =========================================================
    // 3. Câmera Isométrica
    // =========================================================
    // Posicionada em valores positivos altos de X, Y e Z para olhar para a origem
    Ponto posCam(25.0f, 20.0f, 25.0f); 
    Ponto alvo(5.0f, 0.0f, 5.0f); 
    Camera *camera = new Camera(posCam, alvo, Vetor(0, 1, 0));

    Canvas *canvas = new Canvas(
        "Cenário Isométrico em L",
        janela,
        altura,
        largura,
        camera,
        luzAmbiente);

    // =========================================================
    // 4. Planos do Cenário (Formato em L)
    // =========================================================
    string texGrama = "../Assets/textura_grama.png";
    string texCeu = "../Assets/textura-do-ceu_14223-97.png";

    // Chão: Plano XZ na base (Y=0)
    Plano *chao = new Plano(Ponto(0, 0, 0), Vetor(0, 1, 0), texGrama, 0.5f, 30);

    // Parede de Trás (Plano XY em Z=0): Normal aponta para +Z
    Plano *paredeTras = new Plano(Ponto(0, 0, 0), Vetor(0, 0, 1), texCeu, 0.33f, 30);

    // Parede da Esquerda (Plano YZ em X=0): Normal aponta para +X
    Plano *paredeEsq = new Plano(Ponto(0, 0, 0), Vetor(1, 0, 0), texCeu, 0.33f, 30);

    // =========================================================
    // 5. Objetos da Cena (Todos com X, Y, Z positivos)
    // =========================================================
    
    // Centralizado no "pátio"
    Fonte *fonte = new Fonte();
    fonte->transforma(Matriz4x4::translacao(10.0f, 0.0f, 10.0f));

    // Banco de frente para a fonte
    Banco *banco = new Banco();
    banco->transforma(Matriz4x4::translacao(10.0f, 0.0f, 7.0f));

    // Árvores próximas às paredes para preencher o fundo
    Arvore *a1 = new Arvore();
    a1->transforma(Matriz4x4::translacao(3.0f, 0.0f, 3.0f));

    Arvore *a2 = new Arvore();
    a2->transforma(Matriz4x4::translacao(17.0f, 0.0f, 3.0f));

    // Área de jogos
    Mesa *mesa = new Mesa();
    mesa->transforma(Matriz4x4::translacao(5.0f, 0.0f, 12.0f));

    Banqueta *bq1 = new Banqueta();
    bq1->transforma(Matriz4x4::translacao(5.0f, 0.0f, 13.2f));

    // Poste para iluminação lateral
    Poste *poste = new Poste();
    poste->transforma(Matriz4x4::translacao(15.0f, 0.0f, 15.0f));

    // =========================================================
    // 6. Montagem da Cena
    // =========================================================
    canvas->adicionaLuz(&sol);

    canvas->adicionaObjetoCena(chao);
    canvas->adicionaObjetoCena(paredeTras);
    canvas->adicionaObjetoCena(paredeEsq);

    canvas->adicionaObjetoCena(fonte);
    canvas->adicionaObjetoCena(banco);
    canvas->adicionaObjetoCena(a1);
    canvas->adicionaObjetoCena(a2);
    canvas->adicionaObjetoCena(mesa);
    canvas->adicionaObjetoCena(bq1);
    canvas->adicionaObjetoCena(poste);

    // =========================================================
    // 7. Renderização
    // =========================================================
    canvas->geraImagem();
    Interface::inicializar(argc, argv, largura, altura, canvas, "Trabalho Final - Cena em L");
    glutMainLoop();

    return 0;
}