// -*- c++ -*-

#ifndef __VECTOR_H_
#define __VECTOR_H_

class VECTOR
{
public:
    double x, y, z;
};

class MATRIX
{
public:

    double e11;
    double e12;
    double e13;

    double e21;
    double e22;
    double e23;

    double e31;
    double e32;
    double e33;
};

double Mag(const VECTOR &v);
const VECTOR Add(const VECTOR &v1, const VECTOR &v2);
const VECTOR Subtract(const VECTOR &v1, const VECTOR &v2);
const VECTOR Cross(const VECTOR &v1, const VECTOR &v2);
const VECTOR Multiply(const VECTOR &v, double num);
const VECTOR Divide(const VECTOR &v, double num);
void Normalize(VECTOR &v);
double Dot(const VECTOR &v1, const VECTOR &v2);
const VECTOR MVMultiply(const MATRIX &m, const VECTOR &v);
const VECTOR MVxyMultiply(const MATRIX &m, const VECTOR &v);
const VECTOR MVxMultiply(const MATRIX &m, const VECTOR &v);
const VECTOR MVyMultiply(const MATRIX &m, const VECTOR &v);
const VECTOR MVy1Multiply(const MATRIX &m, const VECTOR &v);
const VECTOR MVzMultiply(const MATRIX &m, const VECTOR &v);
const MATRIX MMMultiply(const MATRIX &m1, const MATRIX &m2);

#endif // __VECTOR_H_
