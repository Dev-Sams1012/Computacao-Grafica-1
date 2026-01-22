#include "Cubo.hpp"

Cubo::Cubo(float tam_aresta, Ponto centro_base, Cor Kd, Cor Ke, Cor Ka, int M) : Malha({}, {}, Kd, Ke, Ka, M)
{
    this->tam_aresta = tam_aresta;
    this->centro_base = centro_base;

    double h = tam_aresta / 2.0;
    
    Ponto v0 = Ponto(centro_base.Cord_x - h, centro_base.Cord_y, centro_base.Cord_z - h);
    Ponto v1 = Ponto(centro_base.Cord_x + h, centro_base.Cord_y, centro_base.Cord_z - h);
    Ponto v2 = Ponto(centro_base.Cord_x - h, centro_base.Cord_y, centro_base.Cord_z + h);
    Ponto v3 = Ponto(centro_base.Cord_x + h, centro_base.Cord_y, centro_base.Cord_z + h);
    Ponto v4 = Ponto(centro_base.Cord_x - h, centro_base.Cord_y + tam_aresta, centro_base.Cord_z - h);
    Ponto v5 = Ponto(centro_base.Cord_x + h, centro_base.Cord_y + tam_aresta, centro_base.Cord_z - h);
    Ponto v6 = Ponto(centro_base.Cord_x - h, centro_base.Cord_y + tam_aresta, centro_base.Cord_z + h);
    Ponto v7 = Ponto(centro_base.Cord_x + h, centro_base.Cord_y + tam_aresta, centro_base.Cord_z + h);

    vertices = {v0, v1, v2, v3, v4, v5, v6, v7};

    atualizarFaces();
}

void Cubo::transforma(const Matriz4x4 &M)
{
    for (Ponto &v : this->vertices)
        v = M * v;
    atualizarFaces();
}

void Cubo::atualizarFaces()
{
    faces.clear();

    faces.push_back(Triangulo(vertices[0], vertices[2], vertices[1], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[1], vertices[2], vertices[3], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[4], vertices[5], vertices[6], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[5], vertices[7], vertices[6], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[0], vertices[4], vertices[1], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[1], vertices[4], vertices[5], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[2], vertices[3], vertices[6], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[3], vertices[7], vertices[6], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[0], vertices[2], vertices[4], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[2], vertices[6], vertices[4], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[1], vertices[5], vertices[3], K_d, K_e, K_a, m));
    faces.push_back(Triangulo(vertices[3], vertices[5], vertices[7], K_d, K_e, K_a, m));
}