#include "ObjetoComplexo.hpp"

void ObjetoComplexo::adicionarComponente(Objeto *obj)
{
    componentes.push_back(obj);
}

bool ObjetoComplexo::raioIntercepta(const Ponto &origem, const Vetor &Dr)
{
    float t_min = -1.0;
    double epsilon = 1e-6;
    componenteQueAcertou = nullptr;

    for (auto comp : componentes)
    {
        if (comp->raioIntercepta(origem, Dr))
        {
            if (comp->t_i > epsilon && (t_min < 0 || comp->t_i < t_min))
            {
                t_min = comp->t_i;
                componenteQueAcertou = comp;
            }
        }
    }

    if (componenteQueAcertou)
    {
        this->t_i = componenteQueAcertou->t_i;
        return true;
    }

    return false;
}

void ObjetoComplexo::transforma(const Matriz4x4 &M)
{
    for (auto comp : componentes)
    {
        comp->transforma(M);
    }
}

Vetor ObjetoComplexo::normalEm(const Ponto &P) const
{
    if (!componenteQueAcertou) return Vetor(0,0,0);
    return componenteQueAcertou->normalEm(P);
}

void ObjetoComplexo::renderiza(
    Cor &finalColor,
    const Ponto &origem,
    const Vetor &Dr,
    const Ponto &P_F,
    Cor I_F,
    Cor I_A
) const
{
    if (!componenteQueAcertou)
    {
        finalColor = Cor(0, 0, 0);
        return;
    }

    componenteQueAcertou->renderiza(
        finalColor,
        origem,
        Dr,
        P_F,
        I_F,
        I_A
    );
}

bool ObjetoComplexo::pertenceA(const Objeto* obj) const
{
    if (this == obj)
        return true;

    for (auto comp : componentes)
        if (comp == obj)
            return true;

    return false;
}