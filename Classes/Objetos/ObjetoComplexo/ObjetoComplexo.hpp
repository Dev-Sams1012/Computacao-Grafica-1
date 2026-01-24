#ifndef OBJETO_COMPLEXO_HPP
#define OBJETO_COMPLEXO_HPP

#include <vector>
#include "../ObjetoAbstrato/Objeto.hpp"

struct ObjetoComplexo : Objeto
{
    vector<Objeto *> componentes;
    
    ObjetoComplexo();

    void adicionarComponente(Objeto *obj);

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr, HitInfo &hit) override;

    void renderiza(Cor &finalColor, const HitInfo &hit, const Luz &luz) const override;

    virtual Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;

    bool pertenceA(const Objeto *outro) const override;

    string getNomeObj() const override;
};

#endif