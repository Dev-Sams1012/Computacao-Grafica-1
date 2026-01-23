#include "interface.hpp"

Canvas *Interface::canvasReferencia = nullptr;
int Interface::larguraJanela = 0;
int Interface::alturaJanela = 0;

void Interface::inicializar(int argc, char **argv, int w, int h, Canvas *canvas, string titulo)
{
    canvasReferencia = canvas;
    larguraJanela = w;
    alturaJanela = h;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutCreateWindow(titulo.c_str());

    glutDisplayFunc(Interface::display);

    glutReshapeFunc(Interface::reshape);

    glutKeyboardFunc(Interface::keyboard);

    Interface::criarMenu();
}

void Interface::display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (canvasReferencia)
    {
        float zoomX = (float)larguraJanela / canvasReferencia->nCol;
        float zoomY = (float)alturaJanela / canvasReferencia->nLin;

        float zoomFinal = (zoomX < zoomY) ? zoomX : zoomY;

        int offsetX = (larguraJanela - (canvasReferencia->nCol * zoomFinal)) / 2;
        int offsetY = (alturaJanela - (canvasReferencia->nLin * zoomFinal)) / 2;

        glRasterPos2i(offsetX, offsetY + (canvasReferencia->nLin * zoomFinal));
        glPixelZoom(zoomFinal, -zoomFinal);

        glDrawPixels(
            canvasReferencia->nCol,
            canvasReferencia->nLin,
            GL_RGB,
            GL_FLOAT,
            canvasReferencia->getDados());
    }

    glFlush();
}

void Interface::reshape(int w, int h)
{
    larguraJanela = w;
    alturaJanela = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Interface::keyboard(unsigned char key, int, int)
{
    if (!canvasReferencia)
        return;

    if (key == '+' || key == '=')
    {
        canvasReferencia->camera->zoomIn(1.2f);
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == '-')
    {
        canvasReferencia->geraImagem();
    }
    else if (key == 'r' || key == 'R')
    {
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 'q' || key == 'Q' || key == 27)
        exit(0);
}

void Interface::criarMenu()
{
    int menu = glutCreateMenu(Interface::menuHandler);

    glutAddMenuEntry("Zoom In", 1);
    glutAddMenuEntry("Zoom Out", 2);
    glutAddMenuEntry("Regenerar Cena", 3);
    glutAddMenuEntry("Sair", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Interface::menuHandler(int opcao)
{
    if (!canvasReferencia)
        return;

    if (opcao == 1)
    {
        canvasReferencia->camera->zoomIn(1.2f);
    }
    else if (opcao == 2)
    {
        canvasReferencia->camera->zoomOut(1.2f);
    }
    else if (opcao == 4)
    {
        exit(0);
    }

    canvasReferencia->geraImagem();
    glutPostRedisplay();
}