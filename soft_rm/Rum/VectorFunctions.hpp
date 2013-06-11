#ifndef __VECTOR_FUNCTIONS_HPP__
#define __VECTOR_FUNCTIONS_HPP__
#include "Vector.hpp"
#include "utils.hpp"
#include "Color.hpp"
#include "Matrix.hpp"


/// multiplication of vector by matrix
template<typename T, uint DIM>
Vector<T,DIM> operator*(const Matrix<DIM,DIM> & mat, const Vector<T,DIM> point)
{
    Vector<T,DIM> res;
    T sum;

    REPU(i,DIM) {
        sum = 0;
        REPU(j,DIM) sum += mat(j,i) * point[j];
        res[i] = sum;
    }

    return res;
}


/// Implementacja funkcji wektorowych znanych z glsl na przyklad
namespace vf
{
    /// Wartosc bezwzgledna kazdej wspolrzednej wektora 
    template<typename T, uint DIM>
    Vector<T,DIM> abs(Vector<T,DIM> v) {
        REPU(i,DIM) v[i] = fabs(v[i]);
        return v;
    }

    /// Dlugosc euklidesowa do kwadratu wektora
    template<typename T, uint DIM>
    double lengthSqr(const Vector<T,DIM> & v) {
        double l = 0;
        REPU(i,DIM) l += v[i]*v[i];
        return l;
    }

    /// Dlugosc wektora
    template<typename T, uint DIM>
    double length(const Vector<T,DIM> & v) {
        return sqrt(lengthSqr(v));
    }

    template<typename T, uint DIM>
    Vector<T,DIM> mul(const Vector<T,DIM>& a, const Vector<T,DIM>& b) {
        Vector<T,DIM> res;
        REPU(i,DIM) res[i] = a[i] * b[i];
        return res;
    }

    /// Dot product
    template<typename T, uint DIM>
    double dot(const Vector<T,DIM>& a, const Vector<T,DIM>& b)
    {
        double d = 0.;
        REPU(i,DIM) d += a[i]*b[i];
        return d;
    }

    /// Maksymalna wartosc wspolrzednej
    template<typename T, uint DIM>
    T max(const Vector<T,DIM> & v) {
        T max = v[0];
        REPU(i,DIM) if (max < v[i]) max = v[i];
        return max;
    }

    /// Minimalna wartosc wspolrzednej
    template<typename T, uint DIM>
    T min(const Vector<T,DIM> & v) {
        T min = v[0];
        REPU(i,DIM) if (min > v[i]) min = v[i];
        return min;
    }

    template<typename T, uint DIM>
    Vector<T,DIM> clamp(const Vector<T,DIM> & v) {
        Vector<T,DIM> res;
        REPU(i,DIM) res[i] = ::clamp(v[i],0.,1.);
        return res;
    }

    /// Maksymalna wspolrzedna z wektora i skalara
    template<typename T, int DIM>
    T max(const Vector<T,DIM> &v, T scalar) {
        return std::max(max(v),scalar);
    }

    /// Minimalna wspolrzedna z wektora i skalara
    template<typename T, int DIM>
    T min(const Vector<T,DIM> &v, T scalar) {
        return std::min(min(v),scalar);
    }

    template<typename T, int DIM>
    Vector<T,DIM> mod(const Vector<T,DIM> &v, T module)
    {
        Vector<T,DIM> res;
        auto glslmod = [](T x, T y) -> T { return x - y * floor(x/y); };
        REPU(i,DIM) res[i] = glslmod(v[i], module);
        return res;
    }
    
    template<typename T, int DIM>
    Vector<T,DIM> mod_nolast(const Vector<T,DIM> & v, const Vector<T,DIM-1> & m)
    {
        Vector<T,DIM> res = v;
        auto glslmod = [](T x, T y) -> T { return x - y * floor(x/y); };
        REPU(i,(DIM - 1)) res[i] = glslmod(v[i],m[i]);
        return res;
    }

    template<typename T, int DIM>
    Vector<T,DIM> fmod(const Vector<T,DIM>&v, T module)
    {
        Vector<T,DIM> res;
        auto hlslmod = [](T x, T y) -> T { return x - y * static_cast<int>(x/y); }; // trunc x/y
        REPU(i,DIM) res[i] = hlslmod(v[i], module);
        return res;
    }

    template<typename T>
    uint AsColor(const Vector<T,3>& c) {
        return MakeColor(static_cast<uint>(c[0]*255.),static_cast<uint>(c[1]*255.),static_cast<uint>(c[2]*255.),255);
    }

    template<typename T>
    uint AsColor(const Vector<T,4>& c) {
        return MakeColor(static_cast<uint>(c[0]*255.),static_cast<uint>(c[1]*255.),static_cast<uint>(c[2]*255.),static_cast<uint>(c[3]*255.));
    }
};

#endif //__VECTOR_FUNCTIONS_HPP__
