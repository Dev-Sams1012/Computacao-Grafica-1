#include "Objeto.hpp"

bool Objeto::temSombra(Ponto P_I, Luz luz, Objeto *objeto_atual, vector<Objeto *> objetos)
{
    Vetor L = luz.PF - P_I;
    float distancia_Pi_Pf = sqrtf(produtoEscalar(L, L));
    if (distancia_Pi_Pf <= 0.0f)
        return false;

    Vetor L_dir = normalizar(L);
    float epsilon = 0.001f;

    Ponto Ponto_Luz = ray(P_I, L_dir, distancia_Pi_Pf);

    for (Objeto *objeto : objetos)
    {
        if (objeto != objeto_atual)
        {
            if (objeto->raioIntercepta(P_I, Ponto_Luz))
            {
                if (objeto->t_i > epsilon && objeto->t_i < distancia_Pi_Pf)
                {
                    return true;
                }
            }
        }
    }

    return false;
}