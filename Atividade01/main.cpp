#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

struct Cor{
    int r, g ,b;
};

struct Ponto{
    double Cord_x, Cord_y, Cord_z;

    Ponto(double x, double y, double z){
        Cord_x = x;
        Cord_y = y;
        Cord_z = z;
    }
};

struct Vetor{
    double Cord_x, Cord_y, Cord_z;

    Vetor(double x, double y, double z){
        Cord_x = x;
        Cord_y = y;
        Cord_z = z;
    }
};

/* vetor entre p1 e p2 ( p2 - p1 ) */
Vetor operator-(Ponto p2, Ponto p1){
    return Vetor(p2.Cord_x - p1.Cord_x, p2.Cord_y - p1.Cord_y, p2.Cord_z - p1.Cord_z);
}

/* produto escalar de vetores */
double produtoEscalar(Vetor v1, Vetor v2){
	return (v1.Cord_x * v2.Cord_x + v1.Cord_y * v2.Cord_y + v1.Cord_z * v2.Cord_z);
}

bool RaioInterceptaEsfera(double x, double y, double dJanela, double zEsfera, double rEsfera){

    /* origem do Observador */
    Ponto origem = Ponto(0,0,0);

    /* ponto do canvas */
    Ponto canvas = Ponto(x,y,-dJanela);

    /* direção do raio: origem -> canvas */
    Vetor Dr = canvas - origem;

    /* centro da esfera */
    Ponto centroEsfera = Ponto(0,0,zEsfera);

    /* direção do raio: esfera -> origem */
    Vetor w = origem - centroEsfera;

    /* aplicando o raio na equação da esfera */
    double a = produtoEscalar(Dr,Dr);
    double b = 2*(produtoEscalar(w,Dr));
    double c = produtoEscalar(w,w) - rEsfera*rEsfera;

    /* bhaskara para verificar se o raio bate na esfera ou não */
    double delta = pow(b,2) - 4*a*c;
    if (delta < 0) return false;

    double t1 = (-b + sqrt(delta)) / (2*a);
    double t2 = (-b - sqrt(delta)) / (2*a);
    return (t1 > 0 || t2 > 0);
}

int main(){

    /* janela Real */
    double wJanela = 2.0;
    double hJanela = 2.0;
    double dJanela = 1.0;

    /* esfera */
    double rEsfera = 0.5;
    double zEsfera = -(dJanela + rEsfera);
    Cor esfColor = {256, 0, 0};

    /* cor de fundo [ cinza ] */
    Cor bgColor = {100, 100, 100};

    /* canvas pixels: size_t pois não há valores negativos ( e tirar o warning ) */
    size_t nCol = 800;
    size_t nLin = 800;

    /* tamanho dos pixels */
    double Dx = wJanela/double(nCol); /* casting pois está dividindo um double por um unsingned int - vai ser tratado como double */
    double Dy = hJanela/double(nLin); /* \\ */

    /* matriz 2d: imagem */
    vector<vector<Cor>> imagem(nLin, vector<Cor>(nCol, bgColor)); /* por padrão, tudo está com a cor de fundo */

    for (size_t l = 0; l < nLin; l++){
        for(size_t c = 0; c < nCol; c++){
            double x = -wJanela/2. + Dx/2 + double(c)*Dx; /* posição central no eixo x do pixel - casting para double p tirar o warning */
            double y = hJanela/2. - Dy/2 - double(l)*Dy; /* posição central no eixo y do pixel - \\ */

            if(RaioInterceptaEsfera(x,y, dJanela, zEsfera, rEsfera)) imagem[l][c] = esfColor; /* se tocou, então pinta da cor da esfera. */
        }
    }

    /* "conversão" da matriz 2d para uma imagem ppm */
    ofstream arquivo("imagem_esfera.ppm");
    arquivo << "P3\n" << nCol << " " << nLin << "\n255\n";

    for (size_t l = 0; l < nLin; l++){
        for (size_t c = 0; c < nCol; c++){
            arquivo << imagem[l][c].r << " " << imagem[l][c].g << " " << imagem[l][c].b << " ";
        }

        arquivo << "\n";

    }

    arquivo.close();

    cout << "Imagem gerada em 'imagem_esfera.ppm'" << endl;

    return 0;
}