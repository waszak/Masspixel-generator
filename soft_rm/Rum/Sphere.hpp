#ifndef __OBJECT_SHPEHRE_HPP__
#define __OBJECT_SHPEHRE_HPP__
#include "IObject.hpp"
#include "Vector.hpp"
#include "MatrixGen.hpp"

class Sphere : public IObject
{
public:
	Sphere (Point4D position, double radius) : rad(radius), pos(position) {}
private:
	virtual double dist(const Point4D & point) const {
        double dst = DistancePoints(pos, point);
		return dst - rad;
	}
        
	Point4D pos; // pozycja kuli
	double rad; // promien
};


#endif //__OBJECT_SHPEHRE_HPP__//
