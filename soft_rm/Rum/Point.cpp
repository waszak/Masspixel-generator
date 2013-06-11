#include "Point.hpp"

Point4D NewPoint4D(double x, double y, double z, double w)
{
    Point4D p;
    p[0] = x;  p[1] = y;
    p[2] = z;  p[3] = w;
    return p;
}


Point3D NewPoint3D(double x, double y, double z)
{
    Point3D p;
    p[0] = x;  p[1] = y;
    p[2] = z;
    return p;
}


Vector4D VectorFromPoints(const Point4D & a, const Point4D & b)
{
    Vector4D res(b - a);
    res[3] = 1;
    return res;
}


double DistancePoints(const Point4D & a, const Point4D & b) {
    Point4D tmp(b - a);
    double t = tmp.Length();
    //printf("%f\n", t);
    return t;
}
