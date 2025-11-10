#include "Matriz3x3.hpp"

Matriz3x3::Matriz3x3(float diag)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (i == j)
                m[i][j] = diag;
            else
                m[i][j] = 0.0f;
}

Matriz3x3 Matriz3x3::transposta()
{
    Matriz3x3 T;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            T.m[i][j] = m[j][i];
    return T;
}

Matriz3x3 operator*(Vetor v1, Vetor v2)
{
    Matriz3x3 M;
    M.m[0][0] = v1.Cord_x * v2.Cord_x;
    M.m[0][1] = v1.Cord_x * v2.Cord_y;
    M.m[0][2] = v1.Cord_x * v2.Cord_z;
    M.m[1][0] = v1.Cord_y * v2.Cord_x;
    M.m[1][1] = v1.Cord_y * v2.Cord_y;
    M.m[1][2] = v1.Cord_y * v2.Cord_z;
    M.m[2][0] = v1.Cord_z * v2.Cord_x;
    M.m[2][1] = v1.Cord_z * v2.Cord_y;
    M.m[2][2] = v1.Cord_z * v2.Cord_z;
    return M;
}

Matriz3x3 operator*(Matriz3x3 M, float k)
{
    Matriz3x3 R;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            R.m[i][j] = M.m[i][j] * k;
        }
    }
    return R;
}

Matriz3x3 operator-(Matriz3x3 A, Matriz3x3 B)
{
    Matriz3x3 R;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            R.m[i][j] = A.m[i][j] - B.m[i][j];
        }
    }
    return R;
}

Matriz3x3 operator+(Matriz3x3 A, Matriz3x3 B)
{
    Matriz3x3 R;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            R.m[i][j] = A.m[i][j] + B.m[i][j];
        }
    }
    return R;
}

Vetor operator*(Matriz3x3 M, Vetor v)
{
    return Vetor(
        M.m[0][0] * v.Cord_x + M.m[0][1] * v.Cord_y + M.m[0][2] * v.Cord_z,
        M.m[1][0] * v.Cord_x + M.m[1][1] * v.Cord_y + M.m[1][2] * v.Cord_z,
        M.m[2][0] * v.Cord_x + M.m[2][1] * v.Cord_y + M.m[2][2] * v.Cord_z);
}