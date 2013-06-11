#ifndef __LIGHTING_HPP__
#define __LIGHTING_HPP__
#include "Light.hpp"
#include "IObject.hpp"
#include <vector>

class Scene;
class Raymarcher;

/// Manages lights in scene and allows to compute lightness and shadowing for object
class Lighting : public ISerializable
{
    mutable const Raymarcher* _rm; // brzydki hack...
    mutable int _rayAlive;
public:
    explicit Lighting(Scene* scene = nullptr) : mScene(scene), mAO(true), mSSS(false), mSoftShadow(false) 
    {
        mShadowDelta = 0.001;
        mShadowK     = 2.5;
    }
    
    /// Removes all lights
    void Clear();

    /// Assign lighting to scene
    void SetScene(Scene* scene) { mScene = scene; }

    /// TODO: implement other light models
    /// Compute light for an object in scene using global data
    /// \param obj pointer to object
    /// \param hit_pos object hit place
    /// \param viewer position of viewer
    /// \param obj_normal normal of object in hit_pos
    /// \return unclamped RGB color
    Color<double>::type ComputeLight(IObject* obj, const Vector4D& hit_pos, const Vector4D& obj_normal, const Vector4D& viewer, const Raymarcher* rm, int ray_alive) const {
        _rm = rm;
        _rayAlive = ray_alive;
        return BlinnPhong(obj, hit_pos, viewer, obj_normal);
    }

    /// Computes color of object lighted by set of lights using Blinn-Phong method with optional Ambient Occlusion
    /// SubSurface Scattering and with simulated soft shadowing (tada!).
    /// \param obj pointer to object
    /// \param hit_pos object hit place
    /// \param viewer position of viewer
    /// \param obj_normal normal of object in hit_pos
    /// \return RGB color (unclamped!)
    Color<double>::type BlinnPhong(IObject* obj, const Vector4D &hit_pos, const Vector4D & viewer, const Vector4D& obj_normal) const;

    /// Computes Ambient Occlusion
    /// \param location on object surface
    /// \param obj_normal normal vector of object
    /// \param strength multiplication value of result (bigger value makes AO more visible)
    /// \param i how many steps take
    /// \param delta how big make steps
    /// \return self-shadowing value
    double AmbientOcclusion(const Point4D & location, Point4D obj_normal, double strength = 20., int i = 5, double delta = 0.1) const;

    /// Computes Ambient Occlusion
    /// \param location point on object surface (< epsilon)
    /// \param ray_direction direction of ray
    /// \param strength multiplication value of SSS (bigger = more visible)
    /// \param i how many steps
    /// \param delta how big steps
    /// \return self-shadowing value
    double SubSurfaceScattering(const Point4D & location, Point4D ray_direction, double strength = 10., int i = 5, double delta = 0.05) const;

    /// Compute fake soft shadow
    /// \param location point on object surface
    /// \param lDir light direction
    /// \param k lower makes softer shadow
    /// \param delta how big steps makes during ray marching
    double SoftShadow(const Point4D &location, Point4D & lDir, double lDst, double lPow) const;

    /// Generate light in scene
    /// \param location light location
    /// \param energy light energy
    /// \param color light color
    void AddLight(Point4D location, double energy, Color<double>::type color);

    /// Add light to scene
    /// \param light light options
    void AddLight(Light light);

    ////////////////////////////

    /// Serialize data
    /// \param str output stream
    /// \return modified output stream
    std::ostream& serialize(std::ostream& str) const;

    /// Deserialize data
    /// \param str input stream
    /// \return modified input stream
    std::istream& deserialize(std::istream& str);

private:
    std::vector<Light> mLights;
    bool mAO, mSSS, mSoftShadow;
    double mShadowK, mShadowDelta;
    Scene* mScene;
};

#endif //__LIGHTING_HPP__
