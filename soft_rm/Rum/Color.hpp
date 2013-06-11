#ifndef __COLOR_HPP__
#define __COLOR_HPP__
#include "Vector.hpp"
#include "utils.hpp"

// little endian
#define MakeColor(R,G,B,A) ((B) + ((G) << 8) + ((R) << 16) + ((A) << 24))
#define GetR(COLOR) ((COLOR >> 16) & 0xFF)
#define GetG(COLOR) ((COLOR >> 8) & 0xFF)
#define GetB(COLOR) (COLOR & 0xFF)
#define GetA(COLOR) ((COLOR >> 24) & 0xFF)


/// Kolor to tak naprawde odpowiedni wektor
template<typename T>
struct Color
{
    typedef Vector<T,4> type; // RGBA color

    // zapisuje kolor do BGRA wykonujac uciecie do [0,1]
    static uint PackByClamp(const type& c) {
        return  MakeColor( 
                      static_cast<uint>(clamp(c[0], 0., 1.) * 255.f),
					  static_cast<uint>(clamp(c[1], 0., 1.) * 255.f),
					  static_cast<uint>(clamp(c[2], 0., 1.) * 255.f),
                      static_cast<uint>(clamp(c[3], 0., 1.) * 255.f) );
    };


    //TODO: HDR etc
};

typedef Color<double>::type ColorD;
typedef Color<float>::type  ColorF;

#endif //__COLOR_HPP__
