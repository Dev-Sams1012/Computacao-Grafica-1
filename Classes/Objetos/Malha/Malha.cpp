#include "Malha.hpp"

Malha::Malha(vector<Ponto> v, vector<Triangulo> f, Cor Kd, Cor Ke, Cor Ka, int M) : Objeto(Kd, Ke, Ka, M)
{
    vertices = v;
    faces = f;
    tem_textura = false;
}

Malha::Malha(vector<Ponto> v, vector<Triangulo> f, string arquivoTextura, float escala, int M) : Objeto(Cor(0, 0, 0), Cor(0, 0, 0), Cor(0, 0, 0), M)
{
    vertices = v;
    faces = f;

    textura = stbi_load(arquivoTextura.c_str(), &tex_largura, &tex_altura, &tex_componentes, 3);

    if (textura)
    {
        tem_textura = true;
        for (auto &tri : faces)
        {
            tri.textura = this->textura;
            tri.tex_largura = this->tex_largura;
            tri.tex_altura = this->tex_altura;
            tri.escala_textura = escala;
            tri.tem_textura = true;
        }
    }
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
    return Vetor(0, 0, 0);
}