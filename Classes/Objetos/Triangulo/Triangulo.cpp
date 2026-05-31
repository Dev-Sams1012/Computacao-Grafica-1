#include "Triangulo.hpp"

Triangulo::Triangulo(Ponto p1, Ponto p2, Ponto p0, Cor Kd, Cor Ke, Cor Ka, int M) : Objeto(Kd, Ke, Ka, M)
{
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->tem_textura = false;
    atualizarNormal();
}

Triangulo::Triangulo(Ponto p1, Ponto p2, Ponto p0, unsigned char *texPronta, int largura, int altura, float escala, int M) : Objeto(Cor(1, 1, 1), Cor(1, 1, 1), Cor(0.2, 0.2, 0.2), M)
{
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->textura = texPronta;
    this->tex_largura = largura;
    this->tex_altura = altura;
    this->escala_textura = escala;
    this->tem_textura = (texPronta != nullptr);

    atualizarNormal();
}

void Triangulo::atualizarNormal()
{
    Vetor v0 = p1 - p0;
    Vetor v1 = p2 - p0;
    normal = normalizar(produtoVetorial(v0, v1));
}

bool Triangulo::raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit)
{
    Vetor v0 = p1 - p0;
    Vetor v1 = p2 - p0;

    Vetor n = produtoVetorial(v0, v1);

    float denom = produtoEscalar(Dr, n);
    if (fabs(denom) < epsilon)
        return false;

    float t = produtoEscalar(p0 - origem, n) / denom;
    if (t <= epsilon)
        return false;

    Ponto P = ray(origem, Dr, t);

    Vetor v2 = P - p0;

    float d00 = produtoEscalar(v0, v0);
    float d01 = produtoEscalar(v0, v1);
    float d11 = produtoEscalar(v1, v1);
    float d20 = produtoEscalar(v2, v0);
    float d21 = produtoEscalar(v2, v1);

    float denom_b = d00 * d11 - d01 * d01;
    if (fabs(denom_b) < epsilon)
        return false;

    float u = (d11 * d20 - d01 * d21) / denom_b;
    float v = (d00 * d21 - d01 * d20) / denom_b;

    if (u < 0.0f || v < 0.0f || (u + v) > 1.0f)
        return false;

    if (t > epsilon && t < hit.t)
    {
        hit.t = t;
        hit.objeto = this;
        hit.objetoRaiz = this;
        hit.ponto = P;
        hit.normal = normal;
        return true;
    }

    return false;
}

Cor Triangulo::texturaEm(const Ponto &p) const
{
    Vetor u;
    Vetor v;

    if (fabs(normal.Cord_y) > 0.9)
    {
        u = Vetor(1, 0, 0);
    }
    else
    {
        u = normalizar(produtoVetorial(Vetor(0, 1, 0), normal));
    }
    v = produtoVetorial(normal, u);

    float x = produtoEscalar(p - p0, u);
    float y = produtoEscalar(p - p0, v);

    float u_tex = fmod(x * escala_textura, 1.0f);
    float v_tex = fmod(y * escala_textura, 1.0f);

    if (u_tex < 0)
        u_tex += 1;
    if (v_tex < 0)
        v_tex += 1;

    int px = (int)(u_tex * tex_largura);
    int py = (int)((1 - v_tex) * tex_altura);

    int idx = (py * tex_largura + px) * 3;

    return Cor(
        textura[idx] / 255.0f,
        textura[idx + 1] / 255.0f,
        textura[idx + 2] / 255.0f);
}

void Triangulo::transforma(const Matriz4x4 &M)
{
    p0 = M * p0;
    p1 = M * p1;
    p2 = M * p2;

    atualizarNormal();
}

Vetor Triangulo::normalEm(const Ponto &P) const
{
    return normal;
}