#include "Camera.hpp"

Camera::Camera(Ponto eye, Ponto lookAt, Vetor upGuide)
{
    this->eye = eye;

    forward = normalizar(lookAt - eye);
    right = normalizar(produtoVetorial(forward, upGuide));
    up = produtoVetorial(right, forward);

    d = 1.0f;
    xmin = -1.0f;
    xmax = 1.0f;
    ymin = -1.0f;
    ymax = 1.0f;

    tipo = PERSPECTIVA;
}

void Camera::zoomIn(float fator)
{
    if (fator <= 0.0f)
        return;

    xmin /= fator;
    xmax /= fator;
    ymin /= fator;
    ymax /= fator;
}

void Camera::zoomOut(float fator)
{
    xmin *= fator;
    xmax *= fator;
    ymin *= fator;
    ymax *= fator;
}

void Camera::andaX(float d)
{
    eye = ray(eye, right, d);
}

void Camera::andaY(float d)
{
    eye = ray(eye, up, d);
}

void Camera::andaZ(float d)
{
    eye = ray(eye, forward, d);
}

void Camera::pitch(float ang)
{
    Matriz4x4 R = Matriz4x4::rotacaoEixo(right, ang);
    forward = normalizar(R * forward);
    up      = normalizar(R * up);
}

void Camera::yaw(float ang)
{
    Matriz4x4 R = Matriz4x4::rotacaoEixo(up, ang);
    forward = normalizar(R * forward);
    right   = normalizar(R * right);
}

void Camera::roll(float ang)
{
    Matriz4x4 R = Matriz4x4::rotacaoEixo(forward, ang);
    right = normalizar(R * right);
    up    = normalizar(R * up);
}