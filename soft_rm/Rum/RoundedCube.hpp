#ifndef __OBJECT_ROUNDED_CUBE_HPP__
#define __OBJECT_ROUNDED_CUBE_HPP__
#include "IObject.hpp"
#include "VectorFunctions.hpp"

class RoundedCube : public IObject
{
public:
    RoundedCube(Point4D pos, Point4D size, double r) : _pos(pos), _size(size), _rad(r) {}
private:
    virtual double dist(const Point4D & point) const 
    {
        auto t = (vf::abs(point - _pos) - _size).Length();
        return 1;//vf::max( vf::length<double>(vf::abs(point - _pos) - _size), 0.0)) - _rad;
    }

    Point4D _size, _pos;
    double _rad;
};

#endif //__OBJECT_ROUNDED_CUBE_HPP__
