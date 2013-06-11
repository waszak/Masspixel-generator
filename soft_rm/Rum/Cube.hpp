#ifndef __OBJECT_CUBE_HPP__
#define __OBJECT_CUBE_HPP__
#include "IObject.hpp"
#include "VectorFunctions.hpp"

class Box : public IObject
{
public:
    Box (Point4D position, double size) : mPos(position) { mBox = NewPoint4D(size,size,size,0); }
    Box (Point4D position, Point4D size) : mPos(position), mBox(size) { size[3] = 0; }
private:
	virtual double dist(const Point4D & point) const {
        Point4D toZer = vf::abs(point - mPos) - mBox;
        double m = vf::max(toZer);
        return std::min(m, std::max(vf::length(toZer), 0.0));
	}

	Point4D mPos, mBox; // pozycja
};

#endif //__OBJECT_CUBE_HPP__
