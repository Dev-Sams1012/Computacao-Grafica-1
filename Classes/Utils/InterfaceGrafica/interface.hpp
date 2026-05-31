#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "../../../BibliotecasExternas/freeglut-3.8.0/include/GL/freeglut.h"
#include "../Canvas/Canvas.hpp"

struct Interface
{
    static Canvas *canvasReferencia;
    static int larguraJanela;
    static int alturaJanela;

    static void inicializar(int argc, char **argv, int w, int h, Canvas *canvas, string titulo);

    static void display();

    static void reshape(int w, int h);

    static void keyboard(unsigned char key, int x, int y);

    static void special(int key, int x, int y);

    static void mouse(int button, int state, int x, int y);

    static void criarMenu();

    static void menuHandler(int opcao);
};

#endif