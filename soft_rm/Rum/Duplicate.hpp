#ifndef __OBJECT_DUPLICATE_HPP__
#define __OBJECT_DUPLICATE_HPP__
#include "IObject.hpp"

class Duplicate : public IObject
{
public:
    Duplicate(const IObject * obj, Vector3D m)
    {
        mObj = obj;
        mMod = m;
        REPU(i,3) mHalfMod[i] = m[i] * -0.5;
        mHalfMod[3] = 0;
    }
private:
    virtual double dist(const Point4D& point) const
    {
        return mObj->Distance( vf::mod_nolast(point,mMod) + mHalfMod);
    }
    const IObject* mObj;
    Vector3D mMod;
    Vector4D mHalfMod;
};


#endif //__OBJECT_DUPLICATE_HPP__//
