#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include <math.h>
    #include <stddef.h>

    #include "vector.h"
    #include "debugheap.h"
#endif

// Magnitude of a vector
double Mag(const VECTOR &v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Add two vectors
const VECTOR Add(const VECTOR &v1, const VECTOR &v2)
{
    VECTOR sum;

    sum.x = v1.x + v2.x;
    sum.y = v1.y + v2.y;
    sum.z = v1.z + v2.z;

    return sum;
}

// Subtract the two vectors
const VECTOR Subtract(const VECTOR &v1, const VECTOR &v2)
{
    VECTOR difference;

    difference.x = v1.x - v2.x;
    difference.y = v1.y - v2.y;
    difference.z = v1.z - v2.z;

    return difference;
}

// Compute the cross product of two vectors
const VECTOR Cross(const VECTOR &v1, const VECTOR &v2)
{
    VECTOR product;

    product.x = v1.y * v2.z - v2.y * v1.z;
    product.y = v1.z * v2.x - v2.z * v1.x;
    product.z = v1.x * v2.y - v2.x * v1.y;

    return product;
}

// Multiply by constant
const VECTOR Multiply(const VECTOR &v, double num)
{
    VECTOR product;

    product.x = v.x * num;
    product.y = v.y * num;
    product.z = v.z * num;

    return product;
}

// Divide the vector with a scalar
const VECTOR Divide(const VECTOR &v, double num)
{
    VECTOR product;

    if ((num > -0.0000000000000000000000001) && (num < 0.0000000000000000000000001))
    {
        num = 0.0000000000000000000000001;
    }

    const double one_over_num = 1 / num;
    product.x = v.x * one_over_num;
    product.y = v.y * one_over_num;
    product.z = v.z * one_over_num;

    return product;
}

// Normalize the vector
void Normalize(VECTOR &v)
{
    double len = Mag(v);

    v = Divide(v, len);
}

// Compute the dot product
double Dot(const VECTOR &v, const VECTOR &w)
{
    double product;

    product = v.x * w.x + v.y * w.y + v.z * w.z;

    return product;
}

// Multiply matrix by vector
const VECTOR MVMultiply(const MATRIX &m, const VECTOR &v)
{
    VECTOR product;

    product.x = m.e11 * v.x + m.e12 * v.y + m.e13 * v.z;
    product.y = m.e21 * v.x + m.e22 * v.y + m.e23 * v.z;
    product.z = m.e31 * v.x + m.e32 * v.y + m.e33 * v.z;

    return product;
}

// Multiply matrix by vector -- assume v.z == 0.
const VECTOR MVxyMultiply(const MATRIX &m, const VECTOR &v)
{
    VECTOR product;

    product.x = m.e11 * v.x + m.e12 * v.y;
    product.y = m.e21 * v.x + m.e22 * v.y;
    product.z = m.e31 * v.x + m.e32 * v.y;

    return product;
}

// Multiply matrix by vector -- assume v.y == 0, v.z == 0.
const VECTOR MVxMultiply(const MATRIX &m, const VECTOR &v)
{
    VECTOR product;

    product.x = m.e11 * v.x;
    product.y = m.e21 * v.x;
    product.z = m.e31 * v.x;

    return product;
}

// Multiply matrix by vector -- assume v.x == 0, v.z == 0.
const VECTOR MVyMultiply(const MATRIX &m, const VECTOR &v)
{
    VECTOR product;

    product.x = m.e12 * v.y;
    product.y = m.e22 * v.y;
    product.z = m.e32 * v.y;

    return product;
}

// Multiply matrix by [0 1 0]
const VECTOR MVy1Multiply(const MATRIX &m, const VECTOR &  /*v*/)
{
    VECTOR product;

    product.x = m.e12;
    product.y = m.e22;
    product.z = m.e32;

    return product;
}

// Multiply matrix by vector -- assume v.x == 0, v.y == 0.
const VECTOR MVzMultiply(const MATRIX &m, const VECTOR & v)
{
    VECTOR product;

    product.x = m.e13 * v.z;
    product.y = m.e23 * v.z;
    product.z = m.e33 * v.z;

    return product;
}

// Multiply by matrix by matrix
const MATRIX MMMultiply(const MATRIX &m1, const MATRIX &m2)
{
    MATRIX product;

    product.e11 = m1.e11 * m2.e11 + m1.e12 * m2.e21 + m1.e13 * m2.e31;
    product.e12 = m1.e11 * m2.e12 + m1.e12 * m2.e22 + m1.e13 * m2.e32;
    product.e13 = m1.e11 * m2.e13 + m1.e12 * m2.e23 + m1.e13 * m2.e33;

    product.e21 = m1.e21 * m2.e11 + m1.e22 * m2.e21 + m1.e23 * m2.e31;
    product.e22 = m1.e21 * m2.e12 + m1.e22 * m2.e22 + m1.e23 * m2.e32;
    product.e23 = m1.e21 * m2.e13 + m1.e22 * m2.e23 + m1.e23 * m2.e33;

    product.e31 = m1.e31 * m2.e11 + m1.e32 * m2.e21 + m1.e33 * m2.e31;
    product.e32 = m1.e31 * m2.e12 + m1.e32 * m2.e22 + m1.e33 * m2.e32;
    product.e33 = m1.e31 * m2.e13 + m1.e32 * m2.e23 + m1.e33 * m2.e33;

    return product;
}
