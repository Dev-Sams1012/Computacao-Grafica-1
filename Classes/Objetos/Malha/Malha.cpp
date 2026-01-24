#include "Malha.hpp"

Malha::Malha(vector<Ponto> v, vector<Triangulo> f, Cor Kd, Cor Ke, Cor Ka, int M) : Objeto(Kd, Ke, Ka, M)
{
    vertices = v;
    faces = f;
}

bool Malha::raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit)
{
    bool interceptou = false;

    for (Triangulo &face : faces)
    {
        HitInfo hit_temp = hit;

        if (face.raioIntercepta(origem, Dr, hit_temp))
        {
            if (hit_temp.t > epsilon && hit_temp.t < hit.t)
            {
                hit = hit_temp;
                hit.objeto = this;
                hit.objetoRaiz = this;
                interceptou = true;
            }
        }
    }

    return interceptou;
}

void Malha::transforma(const Matriz4x4 &M)
{
    for (Triangulo &face : faces)
        face.transforma(M);
}

Vetor Malha::normalEm(const Ponto &P) const
{
    return Vetor(0,0,0);
}