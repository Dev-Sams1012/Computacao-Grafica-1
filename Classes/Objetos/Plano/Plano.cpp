#include "Plano.hpp"

Plano::Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M) : Objeto(Kd, Ke, Ka, M)
{
    P_pi = Ppi;
    n_bar = normalizar(nbar);
    tem_textura = false;
    infinito = true;
}

Plano::Plano(Ponto Ppi, Vetor nbar, string arquivoTextura, float escala_tex, int M) : Objeto(Cor(0, 0, 0), Cor(0, 0, 0), Cor(0, 0, 0), M)
{
    P_pi = Ppi;
    n_bar = normalizar(nbar);
    tem_textura = true;
    infinito = true;

    arquivo_textura = arquivoTextura;
    escala_textura = escala_tex;

    textura = stbi_load(arquivoTextura.c_str(), &tex_largura, &tex_altura, &tex_componentes, 3);

    if (!textura)
    {
        cerr << "Erro ao carregar textura: " << arquivoTextura << "\n";
        tem_textura = false;
    }
}

Plano::Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M, Ponto min, Ponto max) : Objeto(Kd, Ke, Ka, M)
{
    P_pi = Ppi;
    n_bar = normalizar(nbar);
    tem_textura = false;
    infinito = false;
    minPt = min;
    maxPt = max;
}

Plano::Plano(Ponto Ppi, Vetor nbar, string arquivoTextura, float escala_tex, int M, Ponto min, Ponto max) : Objeto(Cor(0, 0, 0), Cor(0, 0, 0), Cor(0, 0, 0), M)
{
    P_pi = Ppi;
    n_bar = normalizar(nbar);
    tem_textura = true;
    infinito = false;
    minPt = min;
    maxPt = max;

    arquivo_textura = arquivoTextura;
    escala_textura = escala_tex;

    textura = stbi_load(arquivoTextura.c_str(), &tex_largura, &tex_altura, &tex_componentes, 3);

    if (!textura)
    {
        cerr << "Erro ao carregar textura: " << arquivoTextura << "\n";
        tem_textura = false;
    }
}

Cor Plano::texturaEm(const Ponto &p) const
{
    Vetor u;
    Vetor v;

    if (fabs(n_bar.Cord_y) > 0.9)
    {
        u = Vetor(1, 0, 0);
    }
    else
    {
        u = normalizar(produtoVetorial(Vetor(0, 1, 0), n_bar));
    }
    v = produtoVetorial(n_bar, u);

    float x = produtoEscalar(p - P_pi, u);
    float y = produtoEscalar(p - P_pi, v);

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

bool Plano::raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit)
{
    float denom = produtoEscalar(Dr, n_bar);
    if (fabs(denom) < epsilon)
        return false;

    Vetor w = P_pi - origem;
    float t = produtoEscalar(w, n_bar) / denom;

    if (t > epsilon && t < hit.t)
    {
        Ponto P_I = ray(origem, Dr, t);

        if (!infinito)
        {
            if (P_I.Cord_x < minPt.Cord_x - epsilon || P_I.Cord_x > maxPt.Cord_x + epsilon ||
                P_I.Cord_z < minPt.Cord_z - epsilon || P_I.Cord_z > maxPt.Cord_z + epsilon)
            {
                return false;
            }
        }

        hit.t = t;
        hit.objeto = this;
        hit.objetoRaiz = this;
        hit.ponto = P_I;
        hit.normal = n_bar;
        return true;
    }

    return false;
}

void Plano::transforma(const Matriz4x4 &M)
{
    P_pi = M * P_pi;

    if (!infinito)
    {
        minPt = M * minPt;
        maxPt = M * maxPt;
    }

    Matriz4x4 transp = M.transposta();
    n_bar = transp * n_bar;

    n_bar = normalizar(n_bar);
}

Vetor Plano::normalEm(const Ponto &P) const
{
    return normalizar(n_bar);
}