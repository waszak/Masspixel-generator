#ifndef __RAYMARCHER_HPP__
#define __RAYMARCHER_HPP__
#include "utils.hpp"
#include "Ray.hpp"

class Lighting;
class Scene;
class SceneDesc;


/// Ray marching engine (using sphere tracing technique)
class Raymarcher
{
public:
    explicit Raymarcher(SceneDesc* sceneDesc = nullptr);

    void Setup(uint maxSteps = 64, double maxDist = 100.0, double minDist = 0.05, double epsilon = 0.00005);

    /// Find color of pixel from passing ray
    /// \param ray normalized ray from camera to pixel
    Color<double>::type TraceColor(Ray ray, int alive = 1) const;

    void Assign(SceneDesc* sceneDesc = nullptr);
    
private:
    Lighting* m_light;
    Scene*    m_scene;

    uint   m_maxsteps;
    double m_maxdist;
    double m_mindist;
    double m_epsilon;
};

#endif //__RAYMARCHER_HPP__
