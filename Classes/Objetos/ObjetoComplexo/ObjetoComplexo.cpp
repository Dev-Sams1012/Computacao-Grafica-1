#include "ObjetoComplexo.hpp"

ObjetoComplexo::ObjetoComplexo() : Objeto(Cor(0, 0, 0), Cor(0, 0, 0), Cor(0, 0, 0), 1) {}

void ObjetoComplexo::adicionarComponente(Objeto *obj)
{
    componentes.push_back(obj);
}

bool ObjetoComplexo::raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit)
{
    bool interceptou = false;

    HitInfo hit_temp;
    hit_temp.t = hit.t;

    for (auto comp : componentes)
    {
        if (comp->raioIntercepta(origem, Dr, hit_temp))
        {
            if (hit_temp.t > epsilon && hit_temp.t < hit.t)
            {
                hit = hit_temp;
                hit.objeto = comp;
                hit.objetoRaiz = this;
                interceptou = true;
            }
        }
    }

    return interceptou;
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
    return Vetor(0, 0, 0);
}

void ObjetoComplexo::renderiza(Cor &finalColor, const HitInfo &hit, const Luz &luz) const
{
    hit.objeto->renderiza(finalColor, hit, luz);
}

bool ObjetoComplexo::pertenceA(const Objeto *obj) const
{
    if (this == obj)
        return true;

    for (auto comp : componentes)
        if (comp == obj)
            return true;

    return false;
}

string ObjetoComplexo::getNomeObj() const
{
    return "objeto complexo";
}