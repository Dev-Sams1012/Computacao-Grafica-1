#include "Matriz4x4.hpp"

Matriz4x4::Matriz4x4(float diag)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = (i == j ? diag : 0.0f);
}

Matriz4x4 Matriz4x4::transposta()
{
    Matriz4x4 T;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            T.m[i][j] = m[j][i];
    return T;
}

Matriz4x4 Matriz4x4::translacao(float tx, float ty, float tz)
{
    Matriz4x4 M(1.0f);
    M.m[0][3] = tx;
    M.m[1][3] = ty;
    M.m[2][3] = tz;
    return M;
}

Matriz4x4 Matriz4x4::escala(float sx, float sy, float sz)
{
    Matriz4x4 M(1.0f);
    M.m[0][0] = sx;
    M.m[1][1] = sy;
    M.m[2][2] = sz;
    return M;
}

Matriz4x4 Matriz4x4::rotacaoX(float ang)
{
    float c = cos(ang);
    float s = sin(ang);

    Matriz4x4 M(1.0f);
    M.m[1][1] = c;
    M.m[1][2] = -s;
    M.m[2][1] = s;
    M.m[2][2] = c;
    return M;
}

Matriz4x4 Matriz4x4::rotacaoY(float ang)
{
    float c = cos(ang);
    float s = sin(ang);

    Matriz4x4 M(1.0f);
    M.m[0][0] = c;
    M.m[0][2] = s;
    M.m[2][0] = -s;
    M.m[2][2] = c;
    return M;
}

Matriz4x4 Matriz4x4::rotacaoZ(float ang)
{
    float c = cos(ang);
    float s = sin(ang);

    Matriz4x4 M(1.0f);
    M.m[0][0] = c;
    M.m[0][1] = -s;
    M.m[1][0] = s;
    M.m[1][1] = c;
    return M;
}

Matriz4x4 operator*(const Matriz4x4 &A, const Matriz4x4 &B)
{
    Matriz4x4 R;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            R.m[i][j] = 0;
            for (int k = 0; k < 4; k++)
                R.m[i][j] += A.m[i][k] * B.m[k][j];
        }
    return R;
}

Matriz4x4 operator+(const Matriz4x4 &A, const Matriz4x4 &B)
{
    Matriz4x4 R;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            R.m[i][j] = A.m[i][j] + B.m[i][j];
    return R;
}

Matriz4x4 operator-(const Matriz4x4 &A, const Matriz4x4 &B)
{
    Matriz4x4 R;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            R.m[i][j] = A.m[i][j] - B.m[i][j];
    return R;
}

Matriz4x4 operator*(const Matriz4x4 &M, float k)
{
    Matriz4x4 R;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            R.m[i][j] = M.m[i][j] * k;
    return R;
}

Vetor operator*(const Matriz4x4 &M, const Vetor &v)
{
    float x = M.m[0][0] * v.Cord_x + M.m[0][1] * v.Cord_y + M.m[0][2] * v.Cord_z + M.m[0][3] * v.Cord_w;
    float y = M.m[1][0] * v.Cord_x + M.m[1][1] * v.Cord_y + M.m[1][2] * v.Cord_z + M.m[1][3] * v.Cord_w;
    float z = M.m[2][0] * v.Cord_x + M.m[2][1] * v.Cord_y + M.m[2][2] * v.Cord_z + M.m[2][3] * v.Cord_w;

    return Vetor(x, y, z);
}

Ponto operator*(const Matriz4x4 &M, const Ponto &p)
{
    float x = M.m[0][0] * p.Cord_x + M.m[0][1] * p.Cord_y + M.m[0][2] * p.Cord_z + M.m[0][3] * p.Cord_w;
    float y = M.m[1][0] * p.Cord_x + M.m[1][1] * p.Cord_y + M.m[1][2] * p.Cord_z + M.m[1][3] * p.Cord_w;
    float z = M.m[2][0] * p.Cord_x + M.m[2][1] * p.Cord_y + M.m[2][2] * p.Cord_z + M.m[2][3] * p.Cord_w;
    float w = M.m[3][0] * p.Cord_x + M.m[3][1] * p.Cord_y + M.m[3][2] * p.Cord_z + M.m[3][3] * p.Cord_w;

    return Ponto(x/w, y/w, z/w);
}