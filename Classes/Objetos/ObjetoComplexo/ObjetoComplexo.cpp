#include "ObjetoComplexo.hpp"

void ObjetoComplexo::adicionarComponente(Objeto *obj)
{
    componentes.push_back(obj);
}

bool ObjetoComplexo::raioIntercepta(Ponto origem, Ponto canvas)
{
    float t_min = -1.0;
    double epsilon = 1e-6;
    componenteQueAcertou = nullptr;

    for (auto comp : componentes)
    {
        if (comp->raioIntercepta(origem, canvas) && comp->t_i > epsilon && (t_min < 0 || comp->t_i < t_min))
        {
            t_min = comp->t_i;
            componenteQueAcertou = comp;
        }
    }

    if (componenteQueAcertou)
    {
        t_i = t_min;
        Dr = componenteQueAcertou->Dr;
        return true;
    }

    return false;
}

void ObjetoComplexo::renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A)
{
    if (componenteQueAcertou)
        componenteQueAcertou->renderiza(finalColor, origem, P_F, I_F, I_A);
}