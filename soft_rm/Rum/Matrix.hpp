#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__
#include "utils.hpp"
#include "ISerializable.hpp"
#include "Vector.hpp"
#include "ParserException.hpp"

/// Just a simple "static" (compile-time size) matrix implementation 
/// No range checking for better performance
template <uint M_WIDTH = 4, uint M_HEIGHT = 4, typename T = double>
class Matrix : public ISerializable
{
public:
    Matrix() { memset(mMatrix, 0, sizeof(T) * M_WIDTH * M_HEIGHT); }

    T& operator()(int i, int j) { return mMatrix[i][j]; }
    T operator()(int i, int j) const { return mMatrix[i][j]; }

    template<uint M_H>
    Matrix<M_WIDTH, M_H, T> operator*(const Matrix<M_HEIGHT, M_H, T> & m) const
    {
        Matrix<M_WIDTH, M_H, T> res;
        register T sum;

        REPU(i, M_WIDTH)
            REPU(j,M_HEIGHT)
        {
            sum = 0;
            REPU(k, M_HEIGHT) {
                sum += mMatrix[i][k] * m(k,j);
            }
            res(i,j) = sum;
        }

        return res;
    }

    uint Width() const { return M_WIDTH; }
    uint Height() const { return M_HEIGHT; }

private:
    T mMatrix[M_WIDTH][M_HEIGHT];

    virtual std::ostream& serialize(std::ostream& ostr) const
    {
        ostr << '{';
        REPU(i, M_HEIGHT-1) {
            REPU(j, M_WIDTH) ostr << mMatrix[j][i] << ' ';
            ostr << ',';
        }
        REPU(j,M_WIDTH) ostr << mMatrix[j][M_HEIGHT-1] << ' ';
        ostr << '}';
        return ostr;
    }


	virtual std::istream& deserialize(std::istream& istr)
    {
        char z;
        istr >> z;
        if (z != '{') throw MakeParserException("Expected '{' to start matrix.");

        REPU(i, M_HEIGHT - 1) {
            REPU(j, M_WIDTH) if (!(istr >> mMatrix[j][i])) throw MakeParserException("Expected float-point value in matrix.");
            istr >> z; 
            if (z != ',')     throw MakeParserException("Expected ',' in matrix");
        }

        REPU(j, M_WIDTH) if (!(istr >> mMatrix[j][M_HEIGHT-1])) throw MakeParserException("Expected float-point value in matrix.");

        istr >> z;
        if (z != '}') throw MakeParserException("Expected '}' to end matrix.");

        return istr;
    }
};

typedef Matrix<4,4,double> Matrix4D;
typedef Matrix<4,4,float> Matrix4F;

#endif //__MATRIX_HPP__
