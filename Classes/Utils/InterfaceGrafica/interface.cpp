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

    glutSpecialFunc(Interface::special);

    glutMouseFunc(Interface::mouse);

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
        canvasReferencia->camera->zoomOut(1.2f);
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 'r' || key == 'R')
    {
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 'w' || key == 'W')
    {
        canvasReferencia->camera->andaZ(2.0f);
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 's' || key == 'S')
    {
        canvasReferencia->camera->andaZ(-2.0f);
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 'a' || key == 'A')
    {
        canvasReferencia->camera->andaX(-2.0f);
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 'd' || key == 'D')
    {
        canvasReferencia->camera->andaX(2.0f);
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 'q' || key == 'Q')
    {
        canvasReferencia->camera->andaY(-2.0f);
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 'e' || key == 'E')
    {
        canvasReferencia->camera->andaY(2.0f);
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 'z' || key == 'Z')
    {
        canvasReferencia->camera->roll(0.1f);
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 'c' || key == 'C')
    {
        canvasReferencia->camera->roll(-0.1f);
        canvasReferencia->geraImagem();
        glutPostRedisplay();
    }
    else if (key == 27)
        exit(0);
}
void Interface::special(int key, int, int)
{
    if (!canvasReferencia)
        return;

    if (key == GLUT_KEY_LEFT)
    {
        canvasReferencia->camera->yaw(0.1f);
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        canvasReferencia->camera->yaw(-0.1f);
    }
    else if (key == GLUT_KEY_UP)
    {
        canvasReferencia->camera->pitch(0.1f);
    }
    else if (key == GLUT_KEY_DOWN)
    {
        canvasReferencia->camera->pitch(-0.1f);
    }

    canvasReferencia->geraImagem();
    glutPostRedisplay();
}

void Interface::mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int canvasX = x;
        int canvasY = y;

        Objeto *selecionado = canvasReferencia->pick(canvasX, canvasY);

        if (selecionado)
        {
            selecionado->imprimeInformacoes();
        }
    }
}

void Interface::criarMenu()
{
    int menu = glutCreateMenu(Interface::menuHandler);

    glutAddMenuEntry("Zoom In", 1);
    glutAddMenuEntry("Zoom Out", 2);
    glutAddMenuEntry("Projecao - Perspectiva", 3);
    glutAddMenuEntry("Projecao - Ortografica", 4);
    glutAddMenuEntry("Projecao - Obliqua", 5);
    glutAddMenuEntry("Regenerar Cena", 6);
    glutAddMenuEntry("Sair", 7);

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
    else if (opcao == 3)
    {
        canvasReferencia->camera->tipo = Camera::PERSPECTIVA;
    }
    else if (opcao == 4)
    {
        canvasReferencia->camera->tipo = Camera::ORTOGRAFICA;
    }
    else if (opcao == 5)
    {
        canvasReferencia->camera->tipo = Camera::OBLIQUA;
    }
    else if (opcao == 7)
    {
        exit(0);
    }

    canvasReferencia->geraImagem();
    glutPostRedisplay();
}