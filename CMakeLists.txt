cmake_minimum_required(VERSION 3.10)

project(main LANGUAGES C CXX)

find_package(OpenMP REQUIRED)

set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL "Não construir")
set(FREEGLUT_BUILD_STATIC_LIBS ON CACHE BOOL "Estática")

add_subdirectory(BibliotecasExternas/freeglut-3.8.0)

add_executable(main
        "Atividade07 ( TrabalhoFinal )/main.cpp"
        Classes/Utils/Vetor/Vetor.cpp
        Classes/Utils/Ponto/Ponto.cpp
        Classes/Utils/Matriz/Matriz3x3.cpp
        Classes/Utils/Matriz/Matriz4x4.cpp
        Classes/Utils/Quaternio/Quaternio.cpp
        Classes/Utils/Canvas/Canvas.cpp
        Classes/Utils/Janela/Janela.cpp
        Classes/Utils/Luz/LuzDirecional/LuzDirecional.cpp
        Classes/Utils/Luz/LuzPontual/LuzPontual.cpp
        Classes/Utils/Luz/LuzSpot/LuzSpot.cpp
        Classes/Utils/Camera/Camera.cpp
        Classes/Utils/InterfaceGrafica/interface.cpp
        Classes/Objetos/ObjetoAbstrato/Objeto.cpp
        Classes/Objetos/ObjetoComplexo/ObjetoComplexo.cpp
        Classes/Objetos/Cilindro/Cilindro.cpp
        Classes/Objetos/Cone/Cone.cpp
        Classes/Objetos/Esfera/Esfera.cpp
        Classes/Objetos/Plano/Plano.cpp
        Classes/Objetos/Triangulo/Triangulo.cpp
        Classes/Objetos/Malha/Malha.cpp
        Classes/Objetos/Cubo/Cubo.cpp
        Classes/Objetos/Paralelepipedo/Paralelepipedo.cpp
        BibliotecasExternas/stb_image.cpp
      )

target_include_directories(main PRIVATE Classes BibliotecasExternas BibliotecasExternas/freeglut-3.8.0/include)

find_package(OpenGL REQUIRED)

target_link_libraries(main PRIVATE freeglut_static ${OPENGL_LIBRARIES} OpenMP::OpenMP_CXX)

target_compile_definitions(main PRIVATE FREEGLUT_STATIC)