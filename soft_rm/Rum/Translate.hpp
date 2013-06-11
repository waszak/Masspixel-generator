#ifndef __OBJECT_TRANSLATE_HPP__
#define __OBJECT_TRANSLATE_HPP__
#include "IObject.hpp"

/// Translates an object
class Translate : public IObject
{
public:
    Translate(IObject* obj, const Vector3D & trans) : _obj(obj)
    {
        REPU(i,3) _translation[i] = trans[i];
        _translation[3] = 0;
    }
private:
    virtual double dist(const Point4D& point) const
    {
        return _obj->Distance(point - _translation);
    }

    const IObject* _obj;
    Vector4D _translation;
};

#endif //__OBJECT_TRANSLATE_HPP__
