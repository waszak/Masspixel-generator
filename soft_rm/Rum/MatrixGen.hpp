#ifndef __MATRIX_GEN_HPP__
#define __MATRIX_GEN_HPP__
#include "Matrix.hpp"

#define PI2 (3.14159265/180.0)

/// Genrator macierzy danego typu

template<typename T = double>
struct MatrixGen
{
    /// Zwraca macierz identycznosciowa (macierz musi byc kwadratowa!)
    template <uint W, uint H>
    static Matrix<W,H,T> Identity()
    {
        COMPILE_ASSERT(Matrix_must_be_square, W == H);

        Matrix<W,H,T> mat;
        REPU(i,W)
            mat(i,i) = 1;
        
        return mat;
    }

    /// Zwraca macierz translacji
    static Matrix<4,4,T> Translation(T dx, T dy, T dz)
    {
        Matrix<4,4,T> m = Identity<4,4>();
        
        m(3,0) = dx;
        m(3,1) = dy;
        m(3,2) = dz;

        return m;
    }

    /// Macierz rotacji wzglêdem osi X
    static Matrix<4,4,T> RotationX(T angle)
    {
        Matrix<4,4,T> m = Identity<4,4>();
        angle *= PI2;

        m(1,1) = m(2,2) = cos(angle);
        m(2,1) = sin(angle);
        m(1,2) = -m(2,1);

        return m;
    }

    /// Macierz rotacji wzglêdem osi Y
    static Matrix<4,4,T> RotationY(T angle)
    {
        Matrix<4,4,T> m = Identity<4,4>();
        angle *= PI2;

        m(0,0) = m(2,2) = cos(angle);
        m(0,2) = sin(angle);
        m(2,0) = -m(0,2);

        return m;
    }

    /// Macierz rotacji wzglêdem osi Z
    static Matrix<4,4,T> RotationZ(T angle)
    {
        Matrix<4,4,T> m = Identity<4,4>();
        angle *= PI2;

        m(0,0) = m(1,1) = cos(angle);
        m(1,0) = sin(angle);
        m(0,1) = -m(1,0);

        return m;
    }

    /// Macierz rotacji ZXY
    static Matrix<4,4,T> RotationZXY(T ax, T ay, T az) {
        return RotationZ(az) * RotationX(ax) * RotationY(ay);
    }
};


#endif //__MATRIX_GEN_HPP__
