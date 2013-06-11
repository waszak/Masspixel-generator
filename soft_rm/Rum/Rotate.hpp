#ifndef __OBJECT_ROTATE_HPP__
#define __OBJECT_ROTATE_HPP__
#include "IObject.hpp"
#include "VectorFunctions.hpp"

class Rotate : public IObject
{
public:
    Rotate(const IObject* obj, const Vector3D &rotation) : _obj(obj)
    {
        _matrix = MatrixGen<>::RotationZXY(rotation[0], rotation[1], rotation[2]);
    }
private:

    virtual double dist(const Point4D& point) const
    {
        return _obj->Distance(_matrix * point);
    }

    Matrix4D _matrix;
    const IObject* _obj;
};

#endif //__OBJECT_ROTATE_HPP__
