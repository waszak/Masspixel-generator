#ifndef __OBJECT_TRANSROT_HPP__
#define __OBJECT_TRANSROT_HPP__
#include "Matrix.hpp"
#include "IObject.hpp"

class IObject;

/// Enable translate and rotation
class TransRot : public IObject
{
public:
    explicit TransRot(const IObject* object, Matrix<> matrix) : mObj(object), mMat(matrix) { }
private:
    virtual double dist(const Point4D & point) const {
        return mObj->Distance(mMat * point);
    }
    const IObject* mObj;
    Matrix<> mMat;
};


#endif //__OBJECT_TRANSROT_HPP__
