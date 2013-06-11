#ifndef __ICAM_HPP__
#define __ICAM_HPP__
#include "Vector.hpp"
#include "raymarcher.hpp"
#include "ISerializable.hpp"

class Image;

class Camera : public ISerializable
{
public:
    Camera(uint width, uint height, double fov = 45.0);
    Camera();

    void Attach(const Raymarcher* rm = nullptr) { mScene = rm; }

    void SetPosition(Point4D pos) { mPos = pos; }

    /// Render scene
    void Render();

    /// Save render image to file
    /// \param file name of file (with .tga)
    /// \return false if error occurred
    bool Save(std::string file);

    virtual std::istream& deserialize(std::istream& str);
    virtual std::ostream& serialize(std::ostream& str) const;

    Image* Raw() { return mImage; }

    void Setup( SceneDesc* scene );

private:
    void Init();
    const Raymarcher *mScene;
    Point4D mPos;
    double nearClip, mFov;
    double mfovY, mfovX;
    uint mWidth, mHeight;
    Image* mImage;
};

#endif //__ICAM_HPP__
