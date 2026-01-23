#include "Camera.hpp"

Camera::Camera(Ponto eye, Ponto lookAt, Vetor upGuide)
{
    this->eye = eye;

    forward = normalizar(lookAt - eye);        
    right   = normalizar(produtoVetorial(forward, upGuide));
    up      = produtoVetorial(right, forward);

    d = 1.0f;
    xmin = -1.0f;
    xmax =  1.0f;
    ymin = -1.0f;
    ymax =  1.0f;

    tipo = PERSPECTIVA;
}

void Camera::zoomIn(float fator)
{
    if (fator <= 0.0f) return;
    
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