# Computação Gráfica 1 - 2025.2

Este repositório contém as atividades e implementações da disciplina **Computação Gráfica 1**, ministrada pelo professor **Creto Vidal** no semestre **2025.2**.  

Todos os trabalhos foram desenvolvidos em **C++** e envolvem tópicos de renderização, manipulação de objetos 3D, iluminação e câmeras.  

## Estrutura do Repositório

```bash
├── Assets
│   └── (Texturas)
├── Atividade01 ... 06
├── Atividade07 (TrabalhoFinal)
│   ├── main.cpp
│   └── Objetos
│       ├── Banco.hpp
│       ├── Mesa.hpp
│       ├── Poste.hpp
│       └── Tabuleiro.hpp
└── Classes
    ├── Objetos
    │   ├── Cilindro
    │   ├── Cone
    │   ├── Cubo
    │   ├── Esfera
    │   ├── Malha
    │   ├── ObjetoAbstrato
    │   ├── ObjetoComplexo
    │   ├── Paralelepipedo
    │   ├── Plano
    │   └── Triangulo
    └── Utils
        ├── Camera
        ├── Canvas
        ├── HitInfo
        ├── InterfaceGrafica
        ├── Janela
        ├── Luz (Direcional, Pontual, Spot)
        ├── Matriz (3x3, 4x4)
        ├── Ponto
        ├── Quaternio
        └── Vetor
```

- **Classes**: Implementações de objetos geométricos, malhas, câmeras, luzes e utilitários.
- **Atividades**: Exemplos e exercícios realizados ao longo do semestre, e agora, trabalho final da disciplina.
- **Assets**: Texturas utilizadas nos projetos.

## Controles de Navegação

O projeto utiliza a GLUT (OpenGL) para fornecer uma interface interativa que permite navegar pela cena e manipular a visualização, utilizando tais comandos:

- <kbd>W</kbd> / <kbd>S</kbd> - Movimenta a câmera para frente/trás (Eixo Z)

- <kbd>A</kbd> / <kbd>D</kbd> - Movimenta a câmera para esquerda/direita (Eixo X)

- <kbd>Q</kbd> / <kbd>E</kbd> - Movimenta a câmera para baixo/cima (Eixo Y)

- <kbd>+</kbd> / <kbd>-</kbd> - Aplica Zoom In / Zoom Out

- <kbd>Z</kbd> / <kbd>C</kbd> - Rotação lateral da câmera (Roll)

- <kbd>R</kbd> - Regenera a imagem

- <kbd>ESC</kbd> - Fecha a aplicação

## Rotação e Orientação (Setas)

As setas do teclado controlam a direção para onde a câmera está olhando:

- Setas Esquerda/Direita: Giro horizontal da câmera (Yaw)

- Setas Cima/Baixo: Inclinação vertical (Pitch)

## Interação com Mouse

- Botão Esquerdo: Ao clicar em um objeto na cena, o nome da sua estrutura dele é exibida no console (picking).

- Botão Direito: Abre um menu de contexto com opções rápidas de Zoom e Saída.

## Compilação

O projeto é em C++ e pode ser compilado com CMake:

```bash
mkdir build
cd build
cmake ..
make
```

Além disso, é possível apenas executar o arquivo _build\_and\_run.bat_ (se você usa windows), que realiza:

```bash
if not exist build (
    echo Criando pasta build...
    mkdir build
)

cd build

cmake ..

if errorlevel 1 (
    echo Erro no CMake.
    pause
    exit /b
)

cmake --build .

if errorlevel 1 (
    echo Erro na compilacao.
    pause
    exit /b
)

main.exe
pause
```
