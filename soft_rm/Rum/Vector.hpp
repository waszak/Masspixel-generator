#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__
#include "utils.hpp"
#include "ISerializable.hpp"
#include "ParserException.hpp"

/// Static (compile-time dimmension set) vector
template <typename T, uint DIM = 4>
class Vector : public ISerializable
{
    T v[DIM];
public:
	Vector() { memset(v, 0, sizeof(T) * DIM); }

    T operator[](int i) const { return v[i]; }
    T& operator[](int i) { return v[i]; }
    T operator()(int i) const { return v[i]; }
    T& operator()(int i) { return v[i]; }
	
    /// Square of vector length
	T LengthSqr() const { T sum(0); REPU(i,DIM) sum += v[i]*v[i]; return sum; }
	
    /// Vector length
    T Length() const { return sqrt( LengthSqr() ); }

    /// Make copy but with last coordinate value set to 'val'
    Vector<T, DIM> CopyAndSetLast(T val) const {
       Vector<T,DIM> res;
       res[DIM - 1] = val;
       return res;
    }

    /// Sum of two vectors
	Vector<T, DIM> operator+(const Vector<T, DIM> & b) const {
		Vector<T,DIM> res;
        REPU(i,DIM) res(i) = v[i] + b[i];
        return res;
	}

    /// Diff vectors
	Vector<T,DIM> operator-(const Vector<T> & b) const {
        Vector<T,DIM> res;
        REPU(i,DIM) res(i) = v[i] - b[i];
        return res;
	}

    /// Multpily by scalar
	Vector<T,DIM> operator*(T scalar) const {
        Vector<T, DIM> res;
        REPU(i,DIM) res(i) = scalar * v[i];
        return res;
	}

    /// Divide by scalar
	Vector<T,DIM> operator/(T scalar) const {
        Vector<T,DIM> res;
        REPU(i,DIM) res(i) = v[i] / scalar;
        return res;
	}

    /// Vector multiplication (like .* in octave)
	Vector<T,DIM> mul(const Vector<T> & b) const {
        Vector<T,DIM> res;
        REPU(i,DIM) res[i] = v[i] * b[i];
        return res;
	}

    /// Normalized Vector
	Vector<T,DIM> Normalized() const {
		return (*this) / Length();
	}

    /// In-place vector normalization
	Vector<T,DIM>& Norm()
	{
        (*this) = (*this) / Length();
		return *this;
	}

    /// Get dimmension of vector
    uint Dimmension() const { return DIM; }

    ///////////////////////

    virtual std::ostream& serialize(std::ostream& ostr) const
    {
        ostr << "(" << v[0];
        for (int i = 1; i < DIM; ++i)
            ostr << " ," << v[i];
        ostr << ')';
        return ostr;
    }


	virtual std::istream& deserialize(std::istream& istr)
    {
        char z;
        istr >> z;
        if (z != '(') throw MakeParserException("Expected '(' to start vector.");

        if (!(istr >> v[0])) throw MakeParserException("Expected float-point value in vector.");

        for (int i = 1; i < DIM; ++i)
        {
            istr >> z; if (z != ',') throw MakeParserException("Expected ',' in vector.");
            if (!(istr >> v[i]))     throw MakeParserException("Expected float-point value in vector.");
        }

        istr >> z;
        if (z != ')') throw MakeParserException("Expected ')' to end vector.");

        return istr;
    }
};


typedef Vector<double, 4> Vector4D;
typedef Vector<double, 3> Vector3D;
typedef Vector<float, 4>  Vector4F;
typedef Vector<float, 3>  Vector3F;

/// Make 4D vector but using 3D and set last to 1
template<typename T>
Vector<T,4> MakeVector4(T x = 0, T y = 0, T z = 0)
{
    Vector<T,4> res;
    res[0] = x;    res[1] = y;
    res[2] = z;    res[3] = 1;
    return res;
}


/// Rozszerza wektor o rozmiarze DIM na NDIM wymiarow, gdzie reszte dopelnia def
template<typename T, uint DIM, uint NDIM>
Vector<T,NDIM> ExtendVector(const Vector<T,DIM> &v, T def = 0)
{
    COMPILE_ASSERT(valid_size, NDIM > DIM);

    Vector<T,NDIM> res;
    REPU(i,DIM) res[i] = v[i];
    for (uint j = DIM; j < NDIM; ++j) 
        res[i] = def;
    
    return res;
}

#endif //__VECTOR_HPP__
