#include "stdafx.h"
#include "Proxy.hpp"
#include "Objects.hpp"
#include "image.hpp"
#include "ISerializable.hpp"

Proxy::Proxy()
{
    lerr = "No Error";
}


Proxy::~Proxy()
{
}

using Serialize::operator>>;

bool Proxy::Compile(const QString &code)
{
    try
    {
        code.toStdString() >> scene;

        rm.Assign(&scene);

        lerr = "No Error";
    }
    catch (Exception& ex)
    {
        lerr = QString::fromStdString(ex.GetError() + std::string("\n") + ex.GetLocation());
        return false;
    }

    return true;
}

void Proxy::SetMaxSteps(uint steps)
{
    rm.Setup(steps);
}

QImage Proxy::Render(uint width, uint height)
{
    Camera cam(width,height);
    
    cam.Setup(&scene);

    cam.Attach( &rm );
    cam.Render();

    Image* img = cam.Raw();
    return QImage( (unsigned char*) img->Raw(), (int)img->Width(), (int)img->Height(), QImage::Format_ARGB32 );
}

QString Proxy::LastError()
{
    return lerr;
}