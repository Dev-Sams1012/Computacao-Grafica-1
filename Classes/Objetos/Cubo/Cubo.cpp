#include "Cubo.hpp"

Cubo::Cubo(float tam_aresta, Ponto centro_base, Cor Kd, Cor Ke, Cor Ka, int M)
{
    double h = tam_aresta / 2.0;
    Ponto v0 = Ponto(centro_base.Cord_x - h, centro_base.Cord_y, centro_base.Cord_z - h);
    Ponto v1 = Ponto(centro_base.Cord_x + h, centro_base.Cord_y, centro_base.Cord_z - h);
    Ponto v2 = Ponto(centro_base.Cord_x - h, centro_base.Cord_y, centro_base.Cord_z + h);
    Ponto v3 = Ponto(centro_base.Cord_x + h, centro_base.Cord_y, centro_base.Cord_z + h);
    Ponto v4 = Ponto(centro_base.Cord_x - h, centro_base.Cord_y + tam_aresta, centro_base.Cord_z - h);
    Ponto v5 = Ponto(centro_base.Cord_x + h, centro_base.Cord_y + tam_aresta, centro_base.Cord_z - h);
    Ponto v6 = Ponto(centro_base.Cord_x - h, centro_base.Cord_y + tam_aresta, centro_base.Cord_z + h);
    Ponto v7 = Ponto(centro_base.Cord_x + h, centro_base.Cord_y + tam_aresta, centro_base.Cord_z + h);

    vector<Ponto> vertices = {v0, v1, v2, v3, v4, v5, v6, v7};

    Triangulo f0 = Triangulo(v0, v2, v1, Kd, Ke, Ka, M);
    Triangulo f1 = Triangulo(v1, v2, v3, Kd, Ke, Ka, M);
    Triangulo f2 = Triangulo(v4, v5, v6, Kd, Ke, Ka, M);
    Triangulo f3 = Triangulo(v5, v7, v6, Kd, Ke, Ka, M);
    Triangulo f4 = Triangulo(v0, v4, v1, Kd, Ke, Ka, M);
    Triangulo f5 = Triangulo(v1, v4, v5, Kd, Ke, Ka, M);
    Triangulo f6 = Triangulo(v2, v3, v6, Kd, Ke, Ka, M);
    Triangulo f7 = Triangulo(v3, v7, v6, Kd, Ke, Ka, M);
    Triangulo f8 = Triangulo(v0, v2, v4, Kd, Ke, Ka, M);
    Triangulo f9 = Triangulo(v2, v6, v4, Kd, Ke, Ka, M);
    Triangulo f10 = Triangulo(v1, v5, v3, Kd, Ke, Ka, M);
    Triangulo f11 = Triangulo(v3, v5, v7, Kd, Ke, Ka, M);

    vector<Triangulo> faces = {f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11};

    this->K_d = Kd;
    this->K_e = Ke;
    this->K_a = Ka;
    this->m = M;

    this->vertices = vertices;
    this->faces = faces;
}