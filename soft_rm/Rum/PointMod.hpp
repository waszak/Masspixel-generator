#ifndef __OBJECT_POINTMOD_HPP__
#define __OBJECT_POINTMOD_HPP__
#include "IObject.hpp"

/// Enable translate and rotation
class PointMod : public IObject
{
public:
    typedef Point4D (*PointModifierFunc) (const Point4D&);
    explicit PointMod(const IObject* object, PointModifierFunc mod) : mObj(object), mMod(mod) { }
private:
    virtual double dist(const Point4D & point) const {
        mObj->Distance(mMod(point));
    }

    const IObject*    mObj;
    PointModifierFunc mMod;
};


#endif //__OBJECT_POINTMOD_HPP__
