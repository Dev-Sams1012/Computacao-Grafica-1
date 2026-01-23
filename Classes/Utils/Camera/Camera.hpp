#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../Matriz/Matriz4x4.hpp"

struct Camera
{
    Ponto eye;
    Vetor forward;
    Vetor right;
    Vetor up;

    float d;
    float xmin, xmax, ymin, ymax;

    enum TipoProjecao {
        PERSPECTIVA,
        ORTOGRAFICA,
        OBLIQUA
    } tipo;

    Camera(Ponto eye, Ponto lookAt, Vetor upGuide);

    void zoomIn(float fator);
    void zoomOut(float fator);
};

#endif