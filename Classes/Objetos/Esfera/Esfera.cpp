#include "Esfera.hpp"

Esfera::Esfera(Ponto c, float r, Cor Kd, Cor Ke, Cor Ka, int M, bool semi, bool inverter) : Objeto(Kd, Ke, Ka, M)
{
    centro = c;
    raio = r;
    ehSemiesfera = semi;
    inverterCorte = inverter;
}

bool Esfera::raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit)
{
    Vetor w = origem - centro;

    float a = produtoEscalar(Dr, Dr);
    float b = 2.0f * produtoEscalar(w, Dr);
    float c = produtoEscalar(w, w) - raio * raio;

    float delta = b * b - 4 * a * c;
    if (delta < 0) return false;

    float sqrt_delta = sqrt(delta);
    float t1 = (-b - sqrt_delta) / (2 * a);
    float t2 = (-b + sqrt_delta) / (2 * a);

    // Precisamos testar os dois t's para o caso da semiesfera
    float candidatos[2] = {t1, t2};
    bool interceptou = false;

    for (float t_atual : candidatos) {
        if (t_atual > epsilon && t_atual < hit.t) {
            Ponto P_teste = ray(origem, Dr, t_atual);

            // LOGICA DA SEMIESFERA: 
            // Se for semiesfera e o ponto estiver abaixo do centro em Y, ignoramos esse t
            if (ehSemiesfera)
            {
                if (!inverterCorte && P_teste.Cord_y < centro.Cord_y)
                    continue;
                if (inverterCorte && P_teste.Cord_y > centro.Cord_y)
                    continue;
            }

            // Se chegou aqui, é um ponto válido
            hit.t = t_atual;
            hit.objeto = this;
            hit.objetoRaiz = this;
            hit.ponto = P_teste;
            hit.normal = normalizar(hit.ponto - centro);
            interceptou = true;
            break; // Pega o t mais próximo e sai
        }
    }

    return interceptou;
}

Vetor Esfera::normalEm(const Ponto &P) const
{
    return normalizar(P - centro);
}

void Esfera::transforma(const Matriz4x4 &M)
{
    centro = M * centro;
}