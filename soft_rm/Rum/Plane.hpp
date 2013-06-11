#ifndef __OBJECT_PLANE_HPP__
#define __OBJECT_PLANE_HPP__
#include "IObject.hpp"
#include "VectorFunctions.hpp"

class Plane : public IObject
{
public:
    Plane(Point4D pos, Vector4D normal) : mPos(pos), mNor(normal.Normalized()) {}
private:
	virtual double dist(const Point4D & point) const {
        Point4D toZer = point - mPos;
        return vf::dot(toZer, mNor) + mNor[3];
	}
	Point4D mPos, mNor;
};

#endif //__OBJECT_PLANE_HPP__
