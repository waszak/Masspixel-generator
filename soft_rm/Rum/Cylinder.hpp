#ifndef __OBJECT_CYLINDER_HPP__
#define __OBJECT_CYLINDER_HPP__
#include "IObject.hpp"

class Cylinder : public IObject
{
public:
    Cylinder (Point4D position, double rad, double size) : mRad(rad), mSize(size), mPos(position) {}
private:
	virtual double dist(const Point4D & point) const {
        Point4D toZer = point - mPos; // przesuniecie punktu do wspolrzednych obiektu
        Vector<double,2> p;
        p[0] = toZer[0] - mRad;
        p[1] = toZer[2] - mRad;
        return vf::length(p) - mSize;
	}

	Point4D mPos; // pozycja
	double mSize; // wysokosc
    double mRad; // promine
};

#endif //__OBJECT_CYLINDER_HPP__
