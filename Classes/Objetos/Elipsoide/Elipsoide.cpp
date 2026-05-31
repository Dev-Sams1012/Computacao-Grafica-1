#include "Elipsoide.hpp"

Elipsoide::Elipsoide(Ponto c, float R1, float R2, float R3, Cor Kd, Cor Ke, Cor Ka, int M) : Objeto(Kd, Ke, Ka, M)
{
    centro = c;
    r1 = R1, r2 = R2, r3 = R3;
}

bool Elipsoide::raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit)
{
    Vetor w = origem - centro;

    float a = (Dr.Cord_x * Dr.Cord_x) / (r1 * r1) +
              (Dr.Cord_y * Dr.Cord_y) / (r2 * r2) +
              (Dr.Cord_z * Dr.Cord_z) / (r3 * r3);

    float b = 2.0f * ((w.Cord_x * Dr.Cord_x) / (r1 * r1) +
                      (w.Cord_y * Dr.Cord_y) / (r2 * r2) +
                      (w.Cord_z * Dr.Cord_z) / (r3 * r3));

    float c = (w.Cord_x * w.Cord_x) / (r1 * r1) +
              (w.Cord_y * w.Cord_y) / (r2 * r2) +
              (w.Cord_z * w.Cord_z) / (r3 * r3) - 1.0f;

    float delta = b * b - 4 * a * c;
    if (delta < 0)
        return false;

    float sqrt_delta = sqrt(delta);
    float t1 = (-b - sqrt_delta) / (2 * a);
    float t2 = (-b + sqrt_delta) / (2 * a);

    float t = -1.0f;

    if (t1 > epsilon)
        t = t1;
    else if (t2 > epsilon)
        t = t2;
    else
        return false;

    if (t > epsilon && t < hit.t)
    {
        hit.t = t;
        hit.objeto = this;
        hit.objetoRaiz = this;
        hit.ponto = ray(origem, Dr, t);
        hit.normal = normalEm(hit.ponto);
        return true;
    }
    return false;
}

Vetor Elipsoide::normalEm(const Ponto &P) const
{
    Vetor n = Vetor(((P.Cord_x - centro.Cord_x) / (r1 * r1)),
                   ((P.Cord_y - centro.Cord_y) / (r2 * r2)),
                   ((P.Cord_z - centro.Cord_z) / (r3 * r3)));

    return normalizar(n);
}

void Elipsoide::transforma(const Matriz4x4 &M)
{
    centro = M * centro;
}