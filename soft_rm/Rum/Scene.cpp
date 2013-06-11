#include "Scene.hpp"
#include "IObject.hpp"
#include <limits>


double Scene::NearestDistance(const Point4D & p) const
{
    double min = std::numeric_limits<double>::max();
    double dst = min;

    for (obj_cit it = mObjects.cbegin(); it != mObjects.cend(); ++it)
        if ( (dst = (*it)->Distance(p)) < min)
            min = dst;
    
    return min;
}


ObjDst Scene::FindNearest(const Point4D & p) const
{
    IObject* obj = NULL;
    double   min = std::numeric_limits<double>::max();
    double   dst = min;
   
    for (obj_it it = mObjects.begin(); it != mObjects.end(); ++it) {
        dst = (*it)->Distance(p);
        if (dst < min) {
            min = dst;
            obj = (*it);
        }
    }
    return ObjDst(obj, min);
}


Scene::~Scene()
{
    // Now only SceneDesc can do it
    //for (obj_it it = mObjects.begin(); it != mObjects.end(); ++it)
    //    delete *it;
}