#ifndef OBJETO_COMPLEXO_HPP
#define OBJETO_COMPLEXO_HPP

#include <vector>
#include "../ObjetoAbstrato/Objeto.hpp"

struct ObjetoComplexo : Objeto
{
    vector<Objeto *> componentes;
    Objeto *componenteQueAcertou = nullptr;

    void adicionarComponente(Objeto *obj);

    bool raioIntercepta(Ponto origem, Ponto canvas) override;

    void renderiza(Cor &finalColor, Ponto origem, Ponto P_F, Cor I_F, Cor I_A) override;

    void transforma(const Matriz4x4 &M) override;
};

#endif