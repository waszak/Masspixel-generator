#ifndef __OBJECT_FRACTAL_HPP__
#define __OBJECT_FRACTAL_HPP__
#include "IObject.hpp"

class Fractal : public IObject
{
public:
private:
    double dist(const Point4D& z) const
    {
        double Scale = 3.f;
        double Offset;
        double r;
        double t;
        int n = 0;
        while (n < 4) {
           if(z[0]+z[1]<0) z.xy = -z.yx; // fold 1
           if(z[0]+z[2]<0) z.xz = -z.zx; // fold 2
           if(z[1]+z[2]<0) z.zy = -z.yz; // fold 3
           t = Offset*(Scale - 1.0);
           z = z*Scale - MakeVector4(t,t,t);
           r = vf::dot(z, z);
           n++;
        }
        return (length(z) ) * pow(Scale, -float(n));
   }
};

#endif //__OBJECT_FRACTAL_HPP__
