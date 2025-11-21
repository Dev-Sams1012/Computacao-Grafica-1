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

Plano::Plano(Ponto Ppi, Vetor nbar, string arquivoTextura, int M)
{
    P_pi = Ppi;
    n_bar = normalizar(nbar);
    m = M;
    tem_textura = true;
    arquivo_textura = arquivoTextura;

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

    float escala = 0.2f;
    float u_tex = fmod(x * escala, 1.0f);
    float v_tex = fmod(y * escala, 1.0f);

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

bool Plano::raioIntercepta(Ponto origem, Ponto canvas)
{
    Vetor Dr_local = canvas - origem;

    Dr = normalizar(Dr_local);

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

void Plano::renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A)
{
    Ponto P_I = ray(origem, Dr, t_i);

    Vetor n = n_bar;

    Vetor l_vetor = normalizar(P_F - P_I);

    Vetor v = -Dr;

    float ln = produtoEscalar(l_vetor, n);

    Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

    Cor k_d_final, k_e_final, k_a_final;
    if (tem_textura)
    {
        k_d_final = texturaEm(P_I);
        k_e_final = k_d_final;
        k_a_final = k_d_final;
    }
    else
    {
        k_d_final = K_d;
        k_e_final = K_e;
        k_a_final = K_a;
    }

    Cor I_diff = operadorArroba(k_d_final, I_F);
    float diff = max(0.0f, ln);
    I_diff.r = I_diff.r * diff;
    I_diff.g = I_diff.g * diff;
    I_diff.b = I_diff.b * diff;

    Cor I_espec = operadorArroba(k_e_final, I_F);
    float vr = max(0.0f, produtoEscalar(v, r));
    float espec = powf(vr, m);
    I_espec.r = I_espec.r * espec;
    I_espec.g = I_espec.g * espec;
    I_espec.b = I_espec.b * espec;

    Cor I_amb = operadorArroba(k_a_final, I_A);

    finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
    finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
    finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
}

void Plano::transforma(const Matriz4x4 &M)
{
    P_pi = M * P_pi;

    Matriz4x4 transp = M.transposta();
    n_bar = transp * n_bar;

    n_bar = normalizar(n_bar);
}