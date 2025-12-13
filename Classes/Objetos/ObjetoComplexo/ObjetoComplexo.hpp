#ifndef OBJETO_COMPLEXO_HPP
#define OBJETO_COMPLEXO_HPP

#include <vector>
#include "../ObjetoAbstrato/Objeto.hpp"

struct ObjetoComplexo : Objeto
{
    vector<Objeto *> componentes;
    Objeto *componenteQueAcertou = nullptr;

    void adicionarComponente(Objeto *obj);

    bool raioIntercepta(const Ponto &origem, const Vetor &Dr) override;

    void renderiza(Cor &finalColor, const Ponto &origem, const Vetor &Dr, const Ponto &P_F, Cor I_F, Cor I_A) const override;

    virtual Vetor normalEm(const Ponto &P) const override;

    void transforma(const Matriz4x4 &M) override;

    bool pertenceA(const Objeto *outro) const override;
};

#endif