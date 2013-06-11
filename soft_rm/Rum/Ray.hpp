#ifndef __RAY_HPP__
#define __RAY_HPP__
#include "Point.hpp"

/// Reprezentacja promienia
struct Ray
{
	enum RayType { RAY_NORMAL, RAY_REFRACTION, RAY_LIGHT, RAY_AO };

	Ray(Vector4D ray, Point4D origin, RayType type = RAY_NORMAL) : mLen(1.0), mRay(ray), mOrigin(origin), mType(type) {}

    Point4D GetEnd()	{ return mOrigin + mRay * mLen; }
	void operator +=(double distance) { mLen += distance; }

	double  mLen;    // dlugosc promienia
	Vector4D mRay;    // znormalizowany wektor promienia
	Point4D  mOrigin; // miejsce zaczepienia
	RayType mType;   // rodzaj promienia
};


#endif //__RAY_HPP__
