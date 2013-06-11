#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#include "Point.hpp"
#include <vector>
#include <string>

class IObject;

/// Represents object and it's distance to point
typedef std::pair<IObject*,double> ObjDst; // object and distance

/// Represents Scene - it contains all objects distance field and given point can find 
/// nearest object and it's distance to it.
class Scene
{
public:
    ~Scene();

    /// Adds object to scene
    void Add(IObject* obj) {  mObjects.push_back(obj); }
    
    /// Finds distance from p to nearest object
    /// \param p point in space ([ x y z 1 ])
    /// \return distance or #INF
    double NearestDistance(const Point4D & p) const;
    
    /// Finds nearest object (if any) and it's distance to point p
    /// \param p point in space
    /// \return pair of object and it's distance to point p
    ObjDst FindNearest(const Point4D & p) const;

private:
    typedef std::vector<IObject*> ObjectList;
    typedef ObjectList::const_iterator obj_cit;
    typedef ObjectList::iterator       obj_it;

    mutable ObjectList mObjects;
};

#endif //__SCENE_HPP__
