#ifndef __OBJECT_TORUS_HPP__
#define __OBJECT_TORUS_HPP__
#include "IObject.hpp"

class Torus : public IObject
{
public:
    Torus(Point4D position, double a, double b) : mPos(position), mA(a), mB(b) {}
private:
    virtual double dist(const Point4D &point) const
    {
        Vector4D p(point - mPos);
        Vector<double,2> t;
        t[0] = sqrt(p[0]*p[0] + p[2]*p[2]) - mA;
        t[1] = p[1];
        return vf::length(t) - mB;
    }

    double mA, mB;
    Point4D mPos;
};

#endif __OBJECT_TORUS_HPP__
