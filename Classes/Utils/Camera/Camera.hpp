#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../Ponto/Ponto.hpp"
#include "../Vetor/Vetor.hpp"
#include "../Matriz/Matriz4x4.hpp"

struct Camera
{
    Ponto eye;
    Vetor forward;
    Vetor right;
    Vetor up;

    Camera(Ponto eye, Ponto lookAt, Vetor upGuide);

    Matriz4x4 viewMatrix() const;
};

#endif