#include "Malha.hpp"

Malha::Malha(vector<Ponto> vertices, vector<Triangulo> faces)
{
    this->vertices = vertices;
    this->faces = faces;
}

bool Malha::raioIntercepta(const Ponto &origem, const Vetor &Dr)
{
    float t_min = -1.0;
    double epsilon = 1e-6;

    for (Triangulo &face : faces)
    {

        if (face.raioIntercepta(origem, Dr))
        {
            if (face.t_i > epsilon && (t_min < 0 || face.t_i < t_min))
            {
                t_min = face.t_i;
                normal = face.normal;
                K_a = face.K_a;
                K_d = face.K_d;
                K_e = face.K_e;
                m = face.m;
            }
        }
    }

    if (t_min < 0)
        return false;
    t_i = t_min;
    return true;
}

void Malha::transforma(const Matriz4x4 &M)
{
    for (Ponto &v : vertices)
    {
        v = M * v;
    }

    for (Triangulo &face : faces)
    {
        face.transforma(M);
    }
}

Vetor Malha::normalEm(const Ponto &P) const
{
    return normal;
}