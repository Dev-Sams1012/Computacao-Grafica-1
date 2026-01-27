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
#include "Objetos/Piso.hpp"
#include "Objetos/Poste.hpp"
#include "Objetos/Tabuleiro.hpp"

using namespace std;

int main(int argc, char **argv)
{
    // =========================================================
    // Configuração
    // =========================================================

    Janela janela(0.5f, 0.7f, 1.0f);
    size_t largura = 500, altura = 500;
    Cor luzAmbiente(0.1f, 0.1f, 0.1f);

    // Posicao inicial
    Ponto posCam(28.0f, 10.0f, 25.0f);
    Ponto alvo(5.0f, 0.0f, 5.0f);

    /*
    // Ponto de fuga 1 ponto
    Ponto posCam(15.0f, 1.7f, 35.0f);
    Ponto alvo(15.0f, 1.7f, 15.0f);
    */

    /*
    // Ponto de fuga 2 pontos
    Ponto posCam(25.0f, 1.7f, 25.0f);
    Ponto alvo(15.0f, 1.7f, 15.0f);
    */

    /*
    // Ponto de fuga 3 pontos
    Ponto posCam(28.0f, 10.0f, 28.0f);
    Ponto alvo(15.0f, 0.0f, 15.0f);
    */

    Camera *camera = new Camera(posCam, alvo, Vetor(0, 1, 0));

    Canvas *canvas = new Canvas(
        "TRABALHO FINAL",
        janela,
        altura,
        largura,
        camera,
        luzAmbiente);

    // =========================================================
    // Iluminação Sol
    // =========================================================

    Vetor dirSol = normalizar(Vetor(-1.0f, -1.5f, -1.0f));
    LuzDirecional sol(dirSol, Cor(1.0f, 0.98f, 0.9f));
    canvas->adicionaLuz(&sol);

    // =========================================================
    // Planos do Cenário
    // =========================================================

    string texGrama = "../Assets/textura_grama.png";
    string texCeu = "../Assets/ceu.png";

    // Plano XZ em Y=0 ( base )
    Plano *chao = new Plano(Ponto(0, 0, 0), Vetor(0, 1, 0), texGrama, 0.5f, 30);
    canvas->adicionaObjetoCena(chao);

    // Plano XY em Z=0
    Plano *paredeTras = new Plano(Ponto(0, 0, 0), Vetor(0, 0, 1), texCeu, 0.01f, 30);
    canvas->adicionaObjetoCena(paredeTras);

    // Plano YZ em X=0
    Plano *paredeEsq = new Plano(Ponto(0, 0, 0), Vetor(1, 0, 0), texCeu, 0.01f, 30);
    canvas->adicionaObjetoCena(paredeEsq);

    // =========================================================
    // Objetos da Cena
    // =========================================================

    Matriz4x4 toOrigem = Matriz4x4::translacao(0.0f, 0.0f, 0.0f);

    Fonte *fonte = new Fonte();
    fonte->transforma(Matriz4x4::translacao(15.0f, 0.0f, 15.0f));
    canvas->adicionaObjetoCena(fonte);

    LuzPontual fonteLuz(Ponto(15.0f, 2.5f, 15.0f), Cor(0.1f, 0.3f, 0.8f));
    canvas->adicionaLuz(&fonteLuz);

    Piso *piso = new Piso();
    piso->transforma(Matriz4x4::translacao(15.0f, 0.0f, 15.0f));
    canvas->adicionaObjetoCena(piso);

    Banco *banco1 = new Banco();
    Ponto pBanco1 = Ponto(13.0f, 0.0f, 7.0f);
    Matriz4x4 rotaBanco1 = Matriz4x4::rotacaoY(M_PI);
    Matriz4x4 transBanco1 = Matriz4x4::translacao(pBanco1.Cord_x, pBanco1.Cord_y, pBanco1.Cord_z);
    banco1->transforma(transBanco1 * rotaBanco1 * toOrigem);
    canvas->adicionaObjetoCena(banco1);

    Banco *banco2 = new Banco();
    Ponto pBanco2 = Ponto(7.0f, 0.0f, 15.0f);
    Matriz4x4 rotaBanco2 = Matriz4x4::rotacaoY(-M_PI / 2);
    Matriz4x4 transBanco2 = Matriz4x4::translacao(pBanco2.Cord_x, pBanco2.Cord_y, pBanco2.Cord_z);
    banco2->transforma(transBanco2 * rotaBanco2 * toOrigem);
    canvas->adicionaObjetoCena(banco2);

    Banco *banco3 = new Banco();
    Ponto pBanco3 = Ponto(20.0f, 0.0f, 10.0f);
    Matriz4x4 rotaBanco3 = Matriz4x4::rotacaoY(120 * M_PI / 180);
    Matriz4x4 transBanco3 = Matriz4x4::translacao(pBanco3.Cord_x, pBanco3.Cord_y, pBanco3.Cord_z);
    banco3->transforma(transBanco3 * rotaBanco3 * toOrigem);
    canvas->adicionaObjetoCena(banco3);

    Banco *banco4 = new Banco();
    Ponto pBanco4 = Ponto(12.0f, 0.0f, 22.0f);
    Matriz4x4 rotaBanco4 = Matriz4x4::rotacaoY(-15 * M_PI / 180);
    Matriz4x4 transBanco4 = Matriz4x4::translacao(pBanco4.Cord_x, pBanco4.Cord_y, pBanco4.Cord_z);
    banco4->transforma(transBanco4 * rotaBanco4 * toOrigem);
    canvas->adicionaObjetoCena(banco4);

    Banco *banco5 = new Banco();
    Ponto pBanco5 = Ponto(19.0f, 0.0f, 21.0f);
    Matriz4x4 rotaBanco5 = Matriz4x4::rotacaoY(30 * M_PI / 180);
    Matriz4x4 transBanco5 = Matriz4x4::translacao(pBanco5.Cord_x, pBanco5.Cord_y, pBanco5.Cord_z);
    banco5->transforma(transBanco5 * rotaBanco5 * toOrigem);
    canvas->adicionaObjetoCena(banco5);

    Banco *banco6 = new Banco();
    Ponto pBanco6 = Ponto(22.0f, 0.0f, 15.0f);
    Matriz4x4 rotaBanco6 = Matriz4x4::rotacaoY(90 * M_PI / 180);
    Matriz4x4 transBanco6 = Matriz4x4::translacao(pBanco6.Cord_x, pBanco6.Cord_y, pBanco6.Cord_z);
    banco6->transforma(transBanco6 * rotaBanco6 * toOrigem);
    canvas->adicionaObjetoCena(banco6);

    Arvore *a1 = new Arvore();
    a1->transforma(Matriz4x4::translacao(10.0f, 0.0f, 10.0f));
    canvas->adicionaObjetoCena(a1);

    Arvore *a2 = new Arvore();
    a2->transforma(Matriz4x4::translacao(17.0f, 0.0f, 8.0f));
    canvas->adicionaObjetoCena(a2);

    Arvore *a3 = new Arvore();
    a3->transforma(Matriz4x4::translacao(8.0f, 0.0f, 20.0f));
    canvas->adicionaObjetoCena(a3);

    Arvore *a4 = new Arvore();
    a4->transforma(Matriz4x4::translacao(22.0f, 0.0f, 12.0f));
    canvas->adicionaObjetoCena(a4);

    Arvore *a5 = new Arvore();
    Ponto pArv5 = Ponto(5.0f, 0.0f, 9.0f);
    Matriz4x4 escArv5 = Matriz4x4::escala(1.0, 1.3, 1.0);
    Matriz4x4 transArv5 = Matriz4x4::translacao(pArv5.Cord_x, pArv5.Cord_y, pArv5.Cord_z);
    a5->transforma(transArv5 * escArv5 * toOrigem);
    canvas->adicionaObjetoCena(a5);

    Arvore *a6 = new Arvore();
    a6->transforma(Matriz4x4::translacao(14.0f, 0.0f, 23.0f));
    canvas->adicionaObjetoCena(a6);

    CarrinhoBaloes *carrinho = new CarrinhoBaloes();
    Ponto pCarrin = Ponto(15.0f, 0.0f, 19.0f);
    Matriz4x4 rotaCarrin = Matriz4x4::rotacaoY(90 * M_PI / 180);
    Matriz4x4 transCarrin = Matriz4x4::translacao(pCarrin.Cord_x, pCarrin.Cord_y, pCarrin.Cord_z);
    carrinho->transforma(transCarrin * rotaCarrin * toOrigem);
    canvas->adicionaObjetoCena(carrinho);

    Mesa *mesa = new Mesa();
    mesa->transforma(Matriz4x4::translacao(19.0f, 0.0f, 16.0f));
    canvas->adicionaObjetoCena(mesa);

    Tabuleiro *tabuleiro = new Tabuleiro();
    tabuleiro->transforma(Matriz4x4::translacao(19.0f, 0.71001f, 16.0f));
    canvas->adicionaObjetoCena(tabuleiro);

    Banqueta *banq1 = new Banqueta();
    banq1->transforma(Matriz4x4::translacao(18.5f, 0.0f, 16.0f));
    canvas->adicionaObjetoCena(banq1);

    Banqueta *banq2 = new Banqueta();
    banq2->transforma(Matriz4x4::translacao(19.5f, 0.0f, 16.0f));
    canvas->adicionaObjetoCena(banq2);

    Poste *poste1 = new Poste();
    poste1->transforma(Matriz4x4::translacao(14.0f, 0.0f, 12.0f));
    canvas->adicionaObjetoCena(poste1);

    Vetor down = Vetor(0.0f, -1.0f, 0.0f);
    float ang = 45 * M_PI / 180;
    Cor luzPoste = Cor(1.0f, 0.85f, 0.45f);

    LuzSpot luz1Pos1 = LuzSpot(Ponto(14.37f, 2.73f, 12.0f), down, ang, luzPoste);
    canvas->adicionaLuz(&luz1Pos1);

    LuzSpot luz2Pos1 = LuzSpot(Ponto(13.63f, 2.73f, 12.0f), down, ang, luzPoste);
    canvas->adicionaLuz(&luz2Pos1);

    Poste *poste2 = new Poste();
    poste2->transforma(Matriz4x4::translacao(21.0f, 0.0f, 18.0f));
    canvas->adicionaObjetoCena(poste2);

    LuzSpot luz1Pos2 = LuzSpot(Ponto(21.37f, 2.73f, 18.0f), down, ang, luzPoste);
    canvas->adicionaLuz(&luz1Pos2);

    LuzSpot luz2Pos2 = LuzSpot(Ponto(20.63f, 2.73f, 18.0f), down, ang, luzPoste);
    canvas->adicionaLuz(&luz2Pos2);

    Poste *poste3 = new Poste();
    poste3->transforma(Matriz4x4::translacao(10.0f, 0.0f, 21.0f));
    canvas->adicionaObjetoCena(poste3);

    LuzSpot luz1Pos3 = LuzSpot(Ponto(10.37f, 2.73f, 21.0f), down, ang, luzPoste);
    canvas->adicionaLuz(&luz1Pos3);

    LuzSpot luz2Pos3 = LuzSpot(Ponto(9.63f, 2.73f, 21.0f), down, ang, luzPoste);
    canvas->adicionaLuz(&luz2Pos3);

    lixeira *lixRed = new lixeira(Cor(0.70f, 0.05f, 0.05f));
    lixRed->transforma(Matriz4x4::translacao(16.0f, 0.0f, 22.0f));
    canvas->adicionaObjetoCena(lixRed);

    lixeira *lixBlu = new lixeira(Cor(0.05f, 0.20f, 0.70f));
    lixBlu->transforma(Matriz4x4::translacao(16.4f, 0.0f, 22.0f));
    canvas->adicionaObjetoCena(lixBlu);

    lixeira *lixYel = new lixeira(Cor(0.80f, 0.70f, 0.05f));
    lixYel->transforma(Matriz4x4::translacao(15.6f, 0.0f, 22.0f));
    canvas->adicionaObjetoCena(lixYel);

    // =========================================================
    // Renderização
    // =========================================================

    canvas->geraImagem();
    Interface::inicializar(argc, argv, largura, altura, canvas, "TRABALHO FINAL - CG1");
    glutMainLoop();

    return 0;
}