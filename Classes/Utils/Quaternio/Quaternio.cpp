#include "Quaternio.hpp"

Quaternio::Quaternio(float w, Vetor v)
{
    this->w = w;
    this->ijk = v;
}

Quaternio Quaternio::conjugado() const
{
    return Quaternio(this->w, -this->ijk);
}

float Quaternio::norma() const
{
    return sqrtf(w * w + powf(ijk.Cord_x, 2) + powf(ijk.Cord_y, 2) + powf(ijk.Cord_z, 2));
}

Quaternio Quaternio::normalizado() const
{
    float n = norma();
    if (n > 0.0f)
        return Quaternio(w / n, ijk / n);
    else
        return Quaternio(1.0f, Vetor(0, 0, 0));
}

Quaternio Quaternio::operator*(const Quaternio &q) const
{
    return Quaternio(w * q.w - produtoEscalar(ijk, q.ijk),
                     w * q.ijk + q.w * ijk + produtoVetorial(ijk, q.ijk));
}

Matriz4x4 Quaternio::toRotationMatrix() const
{
    float x = ijk.Cord_x;
    float y = ijk.Cord_y;
    float z = ijk.Cord_z;
    float w = this->w;

    Matriz4x4 M;

    M.m[0][0] = w * w + x * x - y * y - z * z;
    M.m[0][1] = 2 * (x * y - z * w);
    M.m[0][2] = 2 * (x * z + y * w);
    M.m[0][3] = 0;

    M.m[1][0] = 2 * (x * y + z * w);
    M.m[1][1] = w * w - x * x + y * y - z * z;
    M.m[1][2] = 2 * (y * z - x * w);
    M.m[1][3] = 0;

    M.m[2][0] = 2 * (x * z - y * w);
    M.m[2][1] = 2 * (y * z + x * w);
    M.m[2][2] = w * w - x * x - y * y + z * z;
    M.m[2][3] = 0;

    M.m[3][0] = 0;
    M.m[3][1] = 0;
    M.m[3][2] = 0;
    M.m[3][3] = 1;

    return M;
}