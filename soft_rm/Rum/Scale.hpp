#ifndef __OBJECT_SCALE_HPP__
#define __OBJECT_SCALE_HPP__
#include "IObject.hpp"
#include "VectorFunctions.hpp"

/// Scale an object
class Scale : public IObject
{
public:
    explicit Scale(const IObject* object, double scale = 2.) : mObj(object), mScale(scale) { }
private:
    virtual double dist(const Point4D & point) const {
        return mObj->Distance(scale3D(point)) * mScale;
    }

    Point4D scale3D(const Point4D & p) const
    {
        Point4D v = p / mScale;
        v[3] = p[3];
        return v;
    }

    const IObject* mObj;
    double mScale;
};


#endif //__OBJECT_SCALE_HPP__
