#ifndef __UTILS_HPP__
#define __UTILS_HPP__
#include <string>
#include "Exception.hpp"
#include <list>
#include <cstdarg>
#include <sstream>
#include <algorithm>

typedef unsigned int uint;
typedef unsigned char byte;

////////////////////////////////////////

template<typename T>
double frand(T p)
{
    return (rand() % 2000 - 1000) * 0.0001;
}

/// Funkcja przycinajaca wartosci value do zakresu [min,max]
template<typename T>
T clamp(T value, T min, T max) { return value < min? min : (value > max? max : value); }

/// Obcinanie wartosci do [0,1] (tj. clamp(value, 0., 1.))
template<typename T>
T saturate(T value) {
    return clamp(value, 0., 1.);
}

/// Interpolacja liniowa, x z przedzialu [0,1]
template<typename T>
T lerp(T a, T b, T x) {
    return a + (x / (b-a));
}

/// Liniowa interpolacja pomiedzy a i b, gdzie x to waga [0,1]
template<typename T>
T mix(T a, T b, T x) {
    return a * (1. - x) + b * x;
}

/// Funkcja plynnie interpolujaca, x z przedzialu [a,b], zwraca [0,1]
/// Pierwsza pochodna zerowa.
template<typename T>
T smoothstep(T a, T b, T x) {
    x = clamp( (x - a)/(b - a), 0., 1.);
    return x*x*(3 - 2*x);
}

/// Funkcja plynnie interpolujaca, x z przedzialu [a,b], zwraca [0,1]
/// Pierwsza i druga pochodna zerowa.
template<typename T>
T smootherstep(T a, T b, T x) {
    x = clamp( (x - a)/(b - a), 0., 1.);
    return x*x*x*(x*(x*6 - 15) + 10);
}

///////////////////////////////////////

#define REP(I,N) for (int I = 0; I < N; ++I)
#define REPU(I,N) for(uint I = 0; I < N; ++I)

// quite a smart way to check a compile-time condition 
#define COMPILE_ASSERT(name, cond)\
    typedef char name[(cond)? 1 : -1]

#define SAFE_RELEASE(X) if (X != NULL) { delete X; X = NULL; }

////////////////////////////////////////

#define toLowercase(STRING) std::transform(STRING.begin(), STRING.end(), STRING.begin(), [](char z) { return tolower(z); })

/// instead of lexical cast
template<typename T>
std::string ToString(const T & object) {
    std::stringstream str;
    str << object;
    return str.str();
}

template<typename T>
std::list<T> arg(int num,...)
{
    va_list in;
    std::list<T> list;

    va_start(in, anything);
    while(num --> 0) list.push_back( va_arg(in, T) );
    va_end(in);

    return list;
}

#endif //__UTILS_HPP__
