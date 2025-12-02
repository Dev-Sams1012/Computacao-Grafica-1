#include "Camera.hpp"

Camera::Camera(Ponto eye, Ponto lookAt, Vetor upGuide)
{
    this->eye = eye;

    forward = normalizar(lookAt - eye);        
    right   = normalizar(produtoVetorial(forward, upGuide));
    up      = produtoVetorial(right, forward);  
}

Matriz4x4 Camera::viewMatrix() const
{
    Matriz4x4 M(1.0f);

    M.m[0][0] = right.Cord_x;
    M.m[0][1] = right.Cord_y;
    M.m[0][2] = right.Cord_z;

    M.m[1][0] = up.Cord_x;
    M.m[1][1] = up.Cord_y;
    M.m[1][2] = up.Cord_z;

    M.m[2][0] = -forward.Cord_x;
    M.m[2][1] = -forward.Cord_y;
    M.m[2][2] = -forward.Cord_z;

    M.m[0][3] = -produtoEscalar(right,   eye - Ponto(0.0f,0.0f,0.0f));
    M.m[1][3] = -produtoEscalar(up,      eye - Ponto(0.0f,0.0f,0.0f));
    M.m[2][3] =  produtoEscalar(forward, eye - Ponto(0.0f,0.0f,0.0f));

    return M;
}