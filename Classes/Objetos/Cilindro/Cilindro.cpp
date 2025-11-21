#include "Cilindro.hpp"

Cilindro::Cilindro(Ponto Cb, float Rb, float H, Vetor dr, bool TemBaseInf, bool TemBaseSup, Cor Kd, Cor Ke, Cor Ka, int m_cor)
{
    Centro_base = Cb;
    Raio_base = Rb;
    Altura = H;
    Eixo = normalizar(dr);
    K_d = Kd;
    K_e = Ke;
    K_a = Ka;
    m = m_cor;
    temBaseInferior = TemBaseInf;
    temBaseSuperior = TemBaseSup;
    Q_Matrix = (Eixo * Eixo) * (1.0f / produtoEscalar(Eixo, Eixo));
    M_Matrix = Matriz3x3(1.0f) - Q_Matrix;
}

bool Cilindro::raioIntercepta(Ponto origem, Ponto canvas)
{
    Vetor Dr_local = canvas - origem;
    Dr = normalizar(Dr_local);

    Vetor w = origem - Centro_base;

    float a = produtoEscalar(M_Matrix * Dr, M_Matrix * Dr);
    float b = 2.0f * produtoEscalar(M_Matrix * Dr, M_Matrix * w);
    float c = produtoEscalar(M_Matrix * w, M_Matrix * w) - powf(Raio_base, 2);

    float delta = powf(b, 2) - 4 * a * c;
    if (delta < 0)
        return false;

    float r1 = (-b + sqrt(delta)) / (2 * a);
    float r2 = (-b - sqrt(delta)) / (2 * a);

    float t_valido = -1;

    if (r1 > 0)
    {
        Ponto P_I = ray(origem, Dr, r1);
        Vetor v_PI = P_I - Centro_base;
        float altura_Pi = produtoEscalar(Eixo, v_PI);
        if (altura_Pi >= 0 && altura_Pi <= Altura)
        {
            t_valido = r1;
        }
    }

    if (r2 > 0)
    {
        Ponto P_I = ray(origem, Dr, r2);
        Vetor v_PI = P_I - Centro_base;
        float altura_Pi = produtoEscalar(Eixo, v_PI);
        if (altura_Pi >= 0 && altura_Pi <= Altura)
        {
            if (t_valido < 0 || r2 < t_valido)
            {
                t_valido = r2;
            }
        }
    }

    if (temBaseInferior)
    {
        float t_base = produtoEscalar(Eixo, Centro_base - origem) / produtoEscalar(Eixo, Dr);
        if (t_base > 0)
        {
            Ponto P_base = ray(origem, Dr, t_base);
            Vetor d = P_base - Centro_base;
            if (produtoEscalar(d, d) <= Raio_base * Raio_base)
            {
                if (t_valido < 0 || t_base < t_valido)
                    t_valido = t_base;
            }
        }
    }
    if (temBaseSuperior)
    {
        Ponto topo = ray(Centro_base, Eixo, Altura);
        float t_topo = produtoEscalar(Eixo, topo - origem) / produtoEscalar(Eixo, Dr);
        if (t_topo > 0)
        {
            Ponto P_topo = ray(origem, Dr, t_topo);
            Vetor d = P_topo - topo;
            if (produtoEscalar(d, d) <= Raio_base * Raio_base)
            {
                if (t_valido < 0 || t_topo < t_valido)
                    t_valido = t_topo;
            }
        }
    }

    if (t_valido > 0)
    {
        t_i = t_valido;
        return true;
    }

    return false;
}

void Cilindro::renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A)
{
    Ponto P_I = ray(origem, Dr, t_i);

    Vetor n = normalizar(M_Matrix * (P_I - Centro_base));

    Vetor l_vetor = normalizar(P_F - P_I);

    Vetor v = -Dr;

    float ln = produtoEscalar(l_vetor, n);

    Vetor r = normalizar(Vetor(2 * ln * n.Cord_x - l_vetor.Cord_x, 2 * ln * n.Cord_y - l_vetor.Cord_y, 2 * ln * n.Cord_z - l_vetor.Cord_z));

    Cor I_diff = operadorArroba(K_d, I_F);
    float diff = max(0.0f, ln);
    I_diff.r = I_diff.r * diff;
    I_diff.g = I_diff.g * diff;
    I_diff.b = I_diff.b * diff;

    Cor I_espec = operadorArroba(K_e, I_F);
    float vr = max(0.0f, produtoEscalar(v, r));
    float espec = powf(vr, m);
    I_espec.r = I_espec.r * espec;
    I_espec.g = I_espec.g * espec;
    I_espec.b = I_espec.b * espec;

    Cor I_amb = operadorArroba(K_a, I_A);

    finalColor.r = min(1.0f, I_diff.r + I_espec.r + I_amb.r);
    finalColor.g = min(1.0f, I_diff.g + I_espec.g + I_amb.g);
    finalColor.b = min(1.0f, I_diff.b + I_espec.b + I_amb.b);
}

void Cilindro::transforma(const Matriz4x4 &M)
{
    Centro_base = M * Centro_base;
    Eixo = normalizar(M * Eixo);
}