cmake_minimum_required(VERSION 3.10)

project(main)
add_executable(main
        "Atividade05/main copy.cpp"
        Classes/Utils/Vetor/Vetor.cpp
        Classes/Utils/Ponto/Ponto.cpp
        Classes/Utils/Matriz3x3/Matriz3x3.cpp
        Classes/Utils/Janela/Canvas.cpp
        Classes/Utils/Janela/Janela.cpp
        Classes/Utils/Janela/Luz.cpp
        Classes/Objetos/ObjetoAbstrato/Objeto.cpp
        Classes/Objetos/Cilindro/Cilindro.cpp
        Classes/Objetos/Cone/Cone.cpp
        Classes/Objetos/Esfera/Esfera.cpp
        Classes/Objetos/Plano/Plano.cpp
        Classes/Objetos/Triangulo/Triangulo.cpp
        Classes/Objetos/Malha/Malha.cpp
        Classes/Objetos/Cubo/Cubo.cpp
      )


target_include_directories(main PRIVATE Classes)