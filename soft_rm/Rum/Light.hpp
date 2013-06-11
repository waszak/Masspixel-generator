#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__
#include "Point.hpp"
#include "Color.hpp"
#include "ISerializable.hpp"

typedef struct Light : public ISerializable
{
    Point4D              mPosition; /// Light position
    Color<double>::type  mColor;    /// Light colour
    double               mPower;    /// Light power

    Light() {}
    Light(Point4D position, Color<double>::type color, double power = 1.) : mPosition(position), mColor(color), mPower(power) {}

    std::istream& deserialize(std::istream& str);
    std::ostream& serialize(std::ostream& str) const;
} Light;

#endif //__LIGHT_HPP__
