#ifndef __IOBJECT_HPP__
#define __IOBJECT_HPP__
#include <iostream>
#include "Point.hpp"
#include "VectorFunctions.hpp"
#include "Material.hpp"

/// Abstract class for representing renderable primitives
class IObject 
{
public:
    IObject() {}
    virtual ~IObject() {}

	/// Return euclidean distance from point to object
    /// \param point point in space, where w = 1
    /// \return distance between point and object
	double Distance(const Point4D& point) const { return dist(point); }

    /// Computes normal vector for object
    /// \param point point in space, where w = 1 and point is near object (almost hit or hit)
    /// \return normal vector
    virtual Vector4D Normal(const Point4D& point) const {
        static double e = 0.00005;
        Vector4D n;

        n[0] = dist(MakeVector4(point[0] + e, point[1], point[2])) - dist(MakeVector4(point[0] - e, point[1], point[2]));
        n[1] = dist(MakeVector4(point[0], point[1] + e, point[2])) - dist(MakeVector4(point[0], point[1] - e, point[2]));
        n[2] = dist(MakeVector4(point[0], point[1], point[2] + e)) - dist(MakeVector4(point[0], point[1], point[2] - e));
      
        return n.Norm();
    }

    /// Object material
    const Material& material() const { return mat; }
    Material& material() { return mat; }

private:
	virtual double dist(const Point4D& point) const = 0;

    Material mat;    
};


/// Just comparator for objects.
struct IObjectCmp {
	bool operator()(const IObject *a, const IObject *b) {
		static Point4D p; // punkt odniesienia
		return a->Distance(p) < b->Distance(p);
	}
};

#endif //__SHAPES_HPP__
