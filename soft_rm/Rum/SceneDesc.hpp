#ifndef __SCENE_DESCRIPTOR_HPP__
#define __SCENE_DESCRIPTOR_HPP__
#include "utils.hpp"
#include "Memory.hpp"
#include "ISerializable.hpp"
#include "Camera.hpp"
#include "Exception.hpp"
#include "Lighting.hpp"

class Scene;
class Raymarcher;

/// Implements Scene Description Languages which enables user
/// to write scene 
class SceneDesc : public ISerializable
{
public:
    SceneDesc() : mValid(false), mScene(nullptr) {}

    Scene*    GetScene()    { return mScene; }
    Lighting* GetLighting() { return &mLighting; }
    Camera&   GetCam()      { return mCam; }

    bool        Valid()     const { return mValid; }
    std::string LastError() const { return mLastError; }

    virtual std::ostream& serialize(std::ostream& ostr) const
    {
        throw MakeException("Not implemented yet");
        return ostr;
    }

	virtual std::istream& deserialize(std::istream& istr);
private:
    void Parse(std::istream & str);

    void BuildScene();

    //////////////////

    Memory mMem;
    Camera mCam;
    Scene* mScene;
    Lighting mLighting;
    bool   mValid;
    std::string mLastError;
};

#endif //__SCENE_DESCRIPTOR_HPP__
