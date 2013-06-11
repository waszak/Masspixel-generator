#include "raymarcher.hpp"
#include "Lighting.hpp"
#include "Scene.hpp"
#include "SceneDesc.hpp"


Raymarcher::Raymarcher(SceneDesc* scene)
{
    Assign(scene);
    Setup();
}


void Raymarcher::Setup(uint maxSteps, double maxDist, double minDist, double epsilon)
{
    m_maxsteps = maxSteps;
    m_mindist = minDist;
    m_maxdist = maxDist;
    m_epsilon = epsilon;
}


void Raymarcher::Assign(SceneDesc* sceneDesc)
{
    if (sceneDesc)
    {
        m_light = sceneDesc->GetLighting();
        m_scene = sceneDesc->GetScene();
    }
    else
    {
        m_light = nullptr;
        m_scene = nullptr;
    }
}


Color<double>::type Raymarcher::TraceColor(Ray ray, int alive) const
{
    const double  maxDst = m_maxdist;
    const double epsilon = m_epsilon;
    const int   maxSteps = m_maxsteps;

    if (alive <= 0) return NewPoint4D(0,0,0,0);
    
    ObjDst hit;
    ray.mLen = m_mindist;
    double dst;
    double dst_sum = 0.0;
    int step = 0;
    Point4D location; // current location
    
    do
    {
        location = ray.GetEnd();  location[3] = 1;
        
        hit = m_scene->FindNearest(location);
        dst = hit.second;
        dst_sum += dst;

        if (dst < epsilon) 
        {
            ray += dst;
            location = ray.GetEnd();  location[3] = 1;
            Color<double>::type color = m_light->ComputeLight(hit.first, location, hit.first->Normal(location), ray.mOrigin, this, alive - 1);
            return color;//Color<double>::PackByClamp(color);
        }

        ray += dst; // make a step
    } while (dst < maxDst && ++step < maxSteps);

    /// sky material... negative glow-like
    return NewPoint4D();//vf::AsColor(NewPoint4D(1.-saturate((double)step / maxSteps),1.-saturate((double)step / maxSteps),1.- saturate((double)step / maxSteps),1.)); 
}


// ambient occlusion
//return MakeColor(static_cast<uint>(128 * ao), static_cast<uint>(198 * ao), static_cast<uint>(167 * ao),255);
//return MakeColor(static_cast<uint>(i * 255), static_cast<uint>(i * 255), static_cast<uint>(i * 255),255);
                
//return MakeColor(static_cast<uint>((127.5 + n[0] * 127.5)), 
//    static_cast<uint>((127.5 + n[1] * 127.5)), 
//    static_cast<uint>((127.5 + n[2] * 127.5)), 
//    255);
//return MakeColor(static_cast<uint>(location[2] / 20 * 255), 255 - static_cast<uint>(step * 2), 255 - static_cast<uint>(step * 4), 255); // hit!
