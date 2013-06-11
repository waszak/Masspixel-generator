#include "Scene.hpp"
#include "Lighting.hpp"
#include "Light.hpp"
#include "VectorFunctions.hpp"
#include "utils.hpp"
#include "raymarcher.hpp"
 

void Lighting::AddLight(Point4D location, double energy, Color<double>::type color)
{
    mLights.push_back( Light(location, color, energy) );
}


void Lighting::AddLight(Light light)
{
    mLights.push_back(light);
}


double Lighting::SoftShadow(const Point4D &location, Point4D & lDir, double lDst, double lPow) const
{
    double res = 1.0;
    const double k = mShadowK * lPow;

    for (double t = 0.00005; t < lDst; )
    {
        double dst = mScene->NearestDistance(location + lDir * t);
        if (dst < 0.0000005) return 0;
        res = std::min(res, k * dst / t);
        t += std::max(res, mShadowDelta);
    }

    return res;
}


Color<double>::type Lighting::BlinnPhong(IObject* obj, const Vector4D &hit_pos, const Vector4D & viewer, const Vector4D& n) const
 {
    const Material& m = obj->material();
    Vector4D lDir;
    Vector4D viewDir(viewer - hit_pos);
    Color<double>::type diffuse, color, tcol;
    double ldst, i;
    double modDiffuse = 1.;
    double shadowFactor = 1.;

    if (mAO) modDiffuse  *= AmbientOcclusion(hit_pos, n, 30, 7, 0.04);

    viewDir.Norm();
    Ray reflection_ray(viewDir - n * (vf::dot(viewDir, n) * -2.0), hit_pos);

    //color = m.diffuse;
    double intensity;
    // for all lights in the scene
    for (auto it = mLights.begin(); it != mLights.end(); ++it)
    {
        // vector from object to light
        lDir = it->mPosition - hit_pos ;
        ldst = lDir.LengthSqr();
        lDir.Norm();
        
        // diffuse
        i = clamp( vf::dot(lDir, n), 0., 1. );
        intensity = (i * it->mPower / ldst);
        diffuse = vf::mul(m.diffuse, it->mColor);
        
        if (m.reflection > 0.005)
            tcol = (diffuse * m.diff + _rm->TraceColor(reflection_ray, _rayAlive - 1) * m.reflection) * modDiffuse;
        else
            tcol = diffuse * modDiffuse;

        // specular
        viewDir = (viewDir + lDir).Norm();
        i = pow(clamp(vf::dot(n, viewDir), 0., 1.), m.specularHardness);
        tcol = tcol + m.specular * (i * it->mPower / ldst);

        if (m.doSSS) tcol = tcol + m.sss * SubSurfaceScattering(hit_pos, viewDir * -1.0, 100, 7, 0.04);

        tcol = tcol * intensity; // diff intensity

        if (mSoftShadow) tcol = tcol * SoftShadow(hit_pos, lDir, ldst, it->mPower);

        color = color + tcol;
    }
    color = m.ambient + color;

    color[3] = 1.;
    return color;
 }


double Lighting::AmbientOcclusion(const Point4D & location, Point4D n, double strength, int i, double delta) const
{
    double ao(0);
    double s = pow(2.0,i); 
    
    for (; i >0; --i) {
        ao += (i * delta - abs(mScene->NearestDistance(location + n*i*delta))) / s;
        s /= 0.5;
    }

    return clamp(1.0 - ao * strength, 0., 1.);
}


double Lighting::SubSurfaceScattering(const Point4D & location, Point4D ray_direction, double strength, int i, double delta) const
{
    return 1. - AmbientOcclusion(location, ray_direction, strength, i, delta);
}


std::ostream& Lighting::serialize(std::ostream& str) const
{
    str << "[ ";

    str << "ao = " << (mAO? "true" : "false") << " ";
    str << "shd = " << (mSoftShadow? "true" : "false") << " ";
    str << '\n';

    for (auto it = mLights.begin(); it != mLights.end(); ++it) {
        str << (*it) << '\n';
    }

    str << " ] ";
    return str;
}


std::istream& Lighting::deserialize(std::istream& str)
{
    std::string token1, token2;
    Light tLight;
    char s;

    Clear();

    if (!(str >> s) || s != '[') throw MakeParserException("Expected '[' for Lighting."); 

    if (!(str >> token1 >> s >> token2) || s != '=') throw MakeParserException("Expected <string> = <string>.");
    if (token1 == "ao") mAO = (token2 == "true"? true : false);

    if (!(str >> token1 >> s >> token2) || s != '=') throw MakeParserException("Expected <string> = <string>.");
    if (token1 == "shd") mSoftShadow = (token2 == "true"? true : false);

    ///TODO!!! WARNING CAN:T WORK YETI
    try
    {
        while (str >> tLight) {
            mLights.push_back(tLight);
        }
    }
    catch (ParserException& e)
    {
        if (e.GetLine() != 666)
            throw e;
        else
        {
            str.unget();
        }
    }

    if (!(str >> s) || s != ']') throw MakeParserException("Expected ']' for Lighting."); 

    return str;
}


void Lighting::Clear()
{
    mLights.clear();
    mScene = nullptr;
    mAO = mSoftShadow = false;
}
