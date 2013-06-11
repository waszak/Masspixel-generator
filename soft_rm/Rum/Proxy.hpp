#ifndef __PROXY_HPP__
#define __PROXY_HPP__

#include "raymarcher.hpp"
#include "Camera.hpp"
#include "SceneDesc.hpp"

/// Makes easier to merge GUI and ray marcher engine
class Proxy
{
public:
    Proxy();
    ~Proxy();

    /// Compiles code and setup scene
    /// \return false if error occured. To get message use LastError()
    bool Compile(const QString &code);

    /// Render image to picture
    QImage Render(uint width, uint height);

    void SetMaxSteps(uint steps);

    /// Gets last error
    QString LastError();
private:
    Raymarcher rm;
    Camera cam;
    SceneDesc scene;
    QString lerr;
};

#endif __PROXY_HPP__
