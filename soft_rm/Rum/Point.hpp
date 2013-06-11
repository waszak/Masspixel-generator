#ifndef __POINT_HPP__
#define __POINT_HPP__
#include "Vector.hpp"

typedef Vector3D Point3D;
typedef Vector4D Point4D;
typedef Vector3F Point3F;
typedef Vector3F Point4F;


Point4D NewPoint4D(double x = 0, double y = 0, double z = 0, double w = 1);
Point3D NewPoint3D(double x = 0, double y = 0, double z = 0);


Vector4D VectorFromPoints(const Point4D & a, const Point4D & b);

double DistancePoints(const Point4D & a, const Point4D & b);

//Vector4D VectorFromPoints(const Point3D & a, const Point3D & b) {
//    return ExtendVector<double,3,4>(b - a, 1);
//}



#endif //__POINT_HPP__
