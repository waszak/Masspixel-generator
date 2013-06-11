#include "Camera.hpp"
#include "Exception.hpp"
#include "raymarcher.hpp"
#include "image.hpp"


Camera::Camera(uint width, uint height, double fov) : mWidth(width), mHeight(height), mFov(fov), mImage(nullptr)
{
    mPos[0] = 0;
    mPos[1] = 0;
    mPos[2] = -1.;
    mPos[3] = 1;
    
    Init();
}


Camera::Camera() : mImage(nullptr), mScene(nullptr), mWidth(0), mHeight(0), mFov(0)
{
}


void Camera::Render()
{
    if (mScene == nullptr)
        throw MakeException("Camera do not have scene to render");
    if (mImage == nullptr)
        throw MakeException("Camera do not have image to render scene");

    REPU(y,mHeight) REPU(x,mWidth)
    {
        Ray ray(MakeVector4<double>((2.0 * x / mWidth - 1.0) * mfovX,
                                    (2.0 * y / mHeight - 1.0) * mfovY,
                                    1.0).Normalized(), mPos);

        (*mImage)(x,y) = Color<double>::PackByClamp(mScene->TraceColor(ray,3));
    }
}


void Camera::Init()
{
    nearClip = 0.1;

    mfovY = -tan(mFov * 0.5);
    mfovX = -mfovY * mWidth / static_cast<double>(mHeight);

    if (mImage != nullptr) {
        if (mImage->Height() == mHeight && mImage->Width() == mWidth) return;
        delete mImage;
    }
        
    mImage = new Image(mWidth, mHeight);
}


bool Camera::Save(std::string file) {
    return Serialize::SaveAs(file, mImage);
}


std::istream& Camera::deserialize(std::istream & str)
{
    char z;
    Vector<unsigned, 2> dim;
    double fov;

    if (!(str >> z) || z != '[') throw MakeParserException("Expected '['");
    str >> mPos >> dim >> fov;
    mWidth  = dim[0];
    mHeight = dim[1];
    if (!(str >> z) || z != ']') throw MakeParserException("Expected ']'");

    Init();

    return str;
}


std::ostream& Camera::serialize(std::ostream & str) const
{
    str << "[ ";
    str << mPos << " (" << mWidth << ", " << mHeight << ") " << mFov << ' ';
    str << " ] ";

    return str;
}

void Camera::Setup( SceneDesc* scene )
{
    if (scene != nullptr)
    {
        //TODO
    }
}
