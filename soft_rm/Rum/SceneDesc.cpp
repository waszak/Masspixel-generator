#include "SceneDesc.hpp"
#include "ParserException.hpp"
#include "ObjectFactory.hpp"
#include "Material.hpp"
#include "Scene.hpp"

void SceneDesc::Parse(std::istream & str)
{
    std::string tok;
    mLighting.Clear();

    while (str >> tok)
    {
        if (tok == "camera" || tok == "cam")
        {
            str >> mCam;
        }
        else if (tok == "material" || tok == "mat")
        {
            std::string name;
            Material mat;

            str >> name;
            str >> mat;

            if (mMem.ExistMaterial(name)) std::cerr << "Warning: Overwriting material of name '" << name <<"'\n";

            mMem.VarMaterial(name) = mat;
        }
        else if (tok == "light")
        {
            str >> mLighting;
        }
        else // just a string not a keyword
        {
            std::string assign;
            str >> assign;

            if (assign == "<-")
            {
                std::string mat;
                if (!(str >> mat) || !mMem.AssignMaterialToObject(mat, tok))
                    throw MakeParserException("Error while trying to assign material '" + tok + "' to object '" + mat + "'.");
            }
            else if (assign == "=")
            {
                IObject* obj = ObjectFactory::Construct(str, &mMem);

                if (obj != nullptr)
                {
                    if (mMem.ExistMaterial(tok)) std::cerr << "Warning: Name '" << tok << "' exist like material name.\n";
            
                    if (mMem.ExistObject(tok)) {
                        // zmiana semantyki! referencje sie popsuja
                        throw MakeParserException("Name '" + tok + "' is already in use as an object name.");
                        //std::cerr << "Warning: Overwriting object of name '" << tok << "'.\n";
                        //delete mMem.VarObject(tok);
                    }

                
                    mMem.VarObject(tok) = obj;
                }
            }
            else 
                throw MakeParserException("Expected '=' in object definition or material assign operator '<-'. ");
        }
    }

    BuildScene();
}


std::istream& SceneDesc::deserialize(std::istream & str)
{
    mValid = false;
    mMem.Clear();
    mLastError = "";

    try
    {
        Parse(str);
        mValid = true;
    } catch(ParserException & ex)
    {
        mLastError = ex.what();
        std::cerr << mLastError << "\n";
        throw ex;
    }

    return str;
}


void SceneDesc::BuildScene()
{
    if (mScene != nullptr)
    {
        delete mScene;
    }

    mScene = new Scene();

    for (auto it = mMem.mObjects.begin(); it != mMem.mObjects.end(); ++it)
    {
        mScene->Add(it->second);
    }

    mLighting.SetScene(mScene);
}
