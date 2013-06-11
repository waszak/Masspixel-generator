#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

#include <string>
#include <map>
#include <algorithm>
#include "Material.hpp"
#include "IObject.hpp"

class Memory
{
public:
    std::map<std::string, IObject*> mObjects;
    ~Memory() { Clear(); }

    Material&  VarMaterial   (const std::string &id)  { return mMaterials[id]; }
    bool       ExistMaterial (const std::string &id) { return mMaterials.count(id) != 0; }
    
    IObject*&  VarObject   (const std::string &id) { return mObjects[id]; }
    bool       ExistObject (const std::string &id) { return mObjects.count(id) != 0; }

    bool AssignMaterialToObject(const std::string & mat, const std::string& obj)
    {
        if (mObjects.count(obj) > 0 && mMaterials.count(mat) > 0)
        {
            mObjects[obj]->material() = mMaterials[mat];
            return true;
        }

        return false;
    }

    void Clear() 
    {
        mMaterials.clear();
        std::for_each(mObjects.begin(), mObjects.end(), [](const std::pair<std::string,IObject*> &it) -> void {delete it.second;} );
        mObjects.clear();
    }
    std::map<std::string, Material> mMaterials;
    Material mDefaultMaterial;
private:
};

#endif //__MEMORY_HPP__
