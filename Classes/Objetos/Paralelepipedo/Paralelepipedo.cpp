#include "Paralelepipedo.hpp"

Paralelepipedo::Paralelepipedo(float largura, float profundidade, float altura, Ponto centro,
                               Cor Kd, Cor Ke, Cor Ka, int M)
{
    K_d = Kd;
    K_e = Ke;
    K_a = Ka;
    m = M;

    float hx = largura / 2.0f;
    float hy = altura / 2.0f;
    float hz = profundidade / 2.0f;

    vertices = {
        Ponto(centro.Cord_x - hx, centro.Cord_y - hy, centro.Cord_z - hz),
        Ponto(centro.Cord_x + hx, centro.Cord_y - hy, centro.Cord_z - hz),
        Ponto(centro.Cord_x - hx, centro.Cord_y - hy, centro.Cord_z + hz),
        Ponto(centro.Cord_x + hx, centro.Cord_y - hy, centro.Cord_z + hz),
        Ponto(centro.Cord_x - hx, centro.Cord_y + hy, centro.Cord_z - hz),
        Ponto(centro.Cord_x + hx, centro.Cord_y + hy, centro.Cord_z - hz),
        Ponto(centro.Cord_x - hx, centro.Cord_y + hy, centro.Cord_z + hz),
        Ponto(centro.Cord_x + hx, centro.Cord_y + hy, centro.Cord_z + hz)};

    atualizarFaces();
}

void Paralelepipedo::atualizarFaces()
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

void Paralelepipedo::transforma(const Matriz4x4 &M)
{
    for (Ponto &v : vertices)
        v = M * v;

    atualizarFaces();
}
