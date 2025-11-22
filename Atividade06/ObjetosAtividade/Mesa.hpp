#ifndef MESA_HPP
#define MESA_HPP

#include "../../Classes/Objetos/ObjetoComplexo/ObjetoComplexo.hpp"
#include "../../Classes/Objetos/Paralelepipedo/Paralelepipedo.hpp"

struct Mesa : ObjetoComplexo
{
    Paralelepipedo *tampo;
    Paralelepipedo *suporte1;
    Paralelepipedo *suporte2;

    Mesa()
    {
        float larguraTampo = 2.5f;
        float profundidadeTampo = 1.5f;
        float espessuraTampo = 0.05f;

        float espessuraSuporte = 0.05f;
        float alturaSuporte = 0.95f;

        float yTampoInferior = -1.0f;

        Ponto centroTampo = Ponto(0.0f, yTampoInferior + espessuraTampo / 2.0f, -10.0f);

        Ponto centroSup1 = Ponto(-larguraTampo / 2.0f + espessuraSuporte / 2.0f, yTampoInferior - alturaSuporte / 2.0f, -10.0f);

        Ponto centroSup2 = Ponto(larguraTampo / 2.0f - espessuraSuporte / 2.0f, yTampoInferior - alturaSuporte / 2.0f, -10.0f);

        Cor corTampo(0.8f, 0.5f, 0.2f);
        Cor corSuportes(0.6f, 0.3f, 0.1f);

        tampo = new Paralelepipedo(larguraTampo, profundidadeTampo, espessuraTampo, centroTampo, corTampo, corTampo, corTampo, 10);

        suporte1 = new Paralelepipedo(espessuraSuporte, profundidadeTampo, alturaSuporte, centroSup1, corSuportes, corSuportes, corSuportes, 10);

        suporte2 = new Paralelepipedo(espessuraSuporte, profundidadeTampo, alturaSuporte, centroSup2, corSuportes, corSuportes, corSuportes, 10);

        adicionarComponente(tampo);
        adicionarComponente(suporte1);
        adicionarComponente(suporte2);

        Matriz4x4 T1 = Matriz4x4::translacao(-centroTampo.Cord_x, -centroTampo.Cord_y, -centroTampo.Cord_z);

        Matriz4x4 R = Matriz4x4::rotacaoY(M_PI/2.0f);

        Matriz4x4 T2 = Matriz4x4::translacao(centroTampo.Cord_x, centroTampo.Cord_y, centroTampo.Cord_z);

        Matriz4x4 transformacaoCompleta = T2 * R * T1;

        this->transforma(transformacaoCompleta);
    }
};

#endif
