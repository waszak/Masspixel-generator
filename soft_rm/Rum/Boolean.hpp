#ifndef __OBJECT_BOOLEAN_HPP__
#define __OBJECT_BOOLEAN_HPP__
#include "IObject.hpp"

/// Enable mix two objects together using boolean operations
class Boolean : public IObject
{
public:
    enum BooleanOperation { BOOL_ADD = 1, BOOL_SUBTRACT_A, BOOL_SUBTRACT_B, BOOL_UNION, BOOL_BLEND };

    /// Construct boolean modificator
    /// \param a first object (A)
    /// \param b second object (B)
    /// \param operation which operation to perform (add, union, subtract)
    Boolean(const IObject*a, const IObject* b, BooleanOperation operation = BOOL_ADD) : mA(a), mB(b)
    {
        switch (operation) {
        case 1: mOperation  = add;        break;
        case 2: mOperation  = subtractab; break;
        case 3: mOperation  = subtractba; break;
        case 4: mOperation  = uniono;     break;
        default: mOperation = blend;
        }
    }

private:
    virtual double dist(const Point4D & point) const {
        return mOperation(point, mA, mB);
    }

    static double blend(const Point4D& p, const IObject* mA, const IObject* mB)
    {
        double ta = mA->Distance(p);
        double tb = mB->Distance(p);
        if (tb < ta) std::swap(ta,tb);
        double fac = smoothstep(ta,tb,tb-ta);
        return mix(ta, tb, fac);
    }

    static double add(const Point4D& point, const IObject*mA, const IObject* mB) {
        return std::min(mA->Distance(point), mB->Distance(point));
    }

    static double subtractab(const Point4D& point, const IObject*mA, const IObject* mB) {
        return std::max(-mA->Distance(point), mB->Distance(point));
    }

    static double subtractba(const Point4D& point, const IObject*mA, const IObject* mB) {
        return std::max(mA->Distance(point), -mB->Distance(point));
    }

    static double uniono(const Point4D& point, const IObject*mA, const IObject* mB) {
        return std::max(mA->Distance(point), mB->Distance(point));
    }

    typedef double (*boolean_op)(const Point4D&, const IObject*, const IObject*);
    boolean_op     mOperation;
    const IObject* mA;
    const IObject* mB;
};


#endif //__OBJECT_BOOLEAN_HPP__
