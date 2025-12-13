#include "Plano.hpp"

Plano::Plano(Ponto Ppi, Vetor nbar, Cor Kd, Cor Ke, Cor Ka, int M)
{
    P_pi = Ppi;
    n_bar = normalizar(nbar);
    K_d = Kd;
    K_e = Ke;
    K_a = Ka;
    m = M;
    tem_textura = false;
}

Plano::Plano(Ponto Ppi, Vetor nbar, string arquivoTextura, float escala_tex, int M)
{
    P_pi = Ppi;
    n_bar = normalizar(nbar);
    m = M;
    tem_textura = true;
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
    Vetor aux;
    if (fabs(n_bar.Cord_x) > 0.9)
        aux = Vetor(0, 1, 0);
    else
        aux = Vetor(1, 0, 0);

    Vetor u = normalizar(produtoVetorial(n_bar, aux));
    Vetor v = normalizar(produtoVetorial(n_bar, u));

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

bool Plano::raioIntercepta(const Ponto &origem, const Vetor &Dr)
{
    float denom = produtoEscalar(Dr, n_bar);
    if (fabs(denom) > 0)
    {
        Vetor w = P_pi - origem;
        float t = produtoEscalar(w, n_bar) / denom;

        if (t > 0)
        {
            t_i = t;
            return true;
        }
    }

    return false;
}

void Plano::transforma(const Matriz4x4 &M)
{
    P_pi = M * P_pi;

    Matriz4x4 transp = M.transposta();
    n_bar = transp * n_bar;

    n_bar = normalizar(n_bar);
}

Vetor Plano::normalEm(const Ponto &P) const
{
    return normalizar(n_bar);
}