# Computação Gráfica 1 - 2025.2

Este repositório contém as atividades e implementações da disciplina **Computação Gráfica 1**, ministrada pelo professor **Creto Vidal** no semestre **2025.2**.  

Todos os trabalhos foram desenvolvidos em **C++** e envolvem tópicos de renderização, manipulação de objetos 3D, iluminação e câmeras.  

## Estrutura do repositório

```bash
├───Assets
├───Atividade01
├───Atividade02
├───Atividade03
├───Atividade04
├───Atividade05
├───Atividade06
├───BibliotecasExternas
├───Classes
│   ├───Objetos
│   │   ├───Cilindro
│   │   ├───Cone
│   │   ├───Cubo
│   │   ├───Esfera
│   │   ├───Malha
│   │   ├───ObjetoAbstrato
│   │   ├───ObjetoComplexo
│   │   ├───Paralelepipedo
│   │   ├───Plano
│   │   └───Triangulo
│   └───Utils
│       ├───Camera
│       ├───Canvas
│       ├───Janela
│       ├───Luz
│       ├───Matriz
│       ├───Ponto
│       └───Vetor
└───TrabalhoFinal
```

- **Classes**: Implementações de objetos geométricos, malhas, câmeras, luzes e utilitários.
- **Atividades**: Exemplos e exercícios realizados ao longo do semestre.
- **Assets**: Texturas, imagens e outros arquivos auxiliares utilizados nos projetos.

## Compilação

O projeto é em C++ e pode ser compilado com CMake:

```bash
mkdir build
cd build
cmake ..
make
