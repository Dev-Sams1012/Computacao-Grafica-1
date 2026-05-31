@echo off
echo ===============================
echo  Build + Run (Windows)
echo ===============================

if not exist build (
    echo Criando pasta build...
    mkdir build
)

echo Acessando a pasta build...
cd build

echo ===============================

echo Configurando o projeto com CMake...
cmake ..

if errorlevel 1 (
    echo Erro no CMake.
    pause
    exit /b
)

echo ===============================

echo Compilando o projeto...
cmake --build .

if errorlevel 1 (
    echo Erro na compilacao.
    pause
    exit /b
)

echo ===============================

echo Executando...
main.exe

pause