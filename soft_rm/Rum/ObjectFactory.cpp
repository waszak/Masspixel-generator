#include "ObjectFactory.hpp"
#include "Objects.hpp"
#include "ParserException.hpp"
#include <sstream>
#include <algorithm>
#include "Memory.hpp"


IObject* ObjectFactory::Construct(const std::string & str, Memory* mem)
{
    std::stringstream stream(str);
    IObject* obj (NULL);

    obj = Construct(stream, mem);

    return obj;
}


IObject* ObjectFactory::Construct(std::istream & str, Memory* mem)
{
    char lb = 0;
    char mod = 0;
    std::string name;
    IObject* object (nullptr);

    str >> lb;

    if (lb == '*')
    {
        str >> name;
        toLowercase(name);

        if (mem->ExistObject(name))
            return mem->VarObject(name);
        else
            throw MakeParserException("No object named '" + name + "' found!");
    }

    if (lb != '[') throw MakeParserException("Expected '['");

    str >> mod;

    try
    {
        switch (mod)
        {
        case '+':// add object
            str >> name;
            toLowercase(name);
            object = CreateObject(name, str);
            break;
        case '%':// add modifier
            str >> name;
            toLowercase(name);
            object = CreateModifier(name, str, mem);
            break;
        default:
            throw MakeParserException("Expected '%' or '+'");
        };
    } catch (ParserException& ex) {
        throw ex;
    }

    return object;
}


IObject* ObjectFactory::CreateModifier(std::string & name, std::istream & str, Memory* mem)
{
    IObject* obj(nullptr);
    IObject *a = nullptr, *b = nullptr;
    std::string tmp;

    try
    {
    if (name == "boolean") 
    {
        str >> tmp;
        toLowercase(tmp);

        if (tmp != "add" && tmp != "+" && tmp != "sub" && tmp != "-" && tmp != "subtract" && tmp != "union" && tmp != "&" && tmp != "blend" && tmp != "~" && tmp != "@")
            throw MakeParserException("Bad parameter for boolean operation.");

        a = Construct(str, mem);
        b = Construct(str, mem);

        if (tmp == "add" || tmp == "+")
            obj = new Boolean(a, b, Boolean::BOOL_ADD);
        else if (tmp == "sub" || tmp == "-" || tmp == "subtract")
            obj = new Boolean(a, b, Boolean::BOOL_SUBTRACT_B);
        else if (tmp == "union" || tmp == "&")
            obj = new Boolean(a, b, Boolean::BOOL_UNION);
        else if (tmp == "blend" || tmp == "~" || tmp == "@")
            obj = new Boolean(a, b, Boolean::BOOL_BLEND);
        else throw MakeParserException("Bad boolean option, expected 'add', 'sub', 'blend' or 'union'");
    }
    else if (name == "translate" || name == "trans")
    {
        Vector3D trans;

        str >> trans;
        a = Construct(str, mem);

        if (a == nullptr) throw MakeParserException("Bad object in translate");

        obj = new Translate(a, trans);
    }
    else if (name == "rotate" || name == "rot")
    {
        Vector3D rot;

        str >> rot;
        a = Construct(str, mem);

        if (a == nullptr) throw MakeParserException("Bad object in rotation");

        obj = new Rotate(a, rot);
    }
    else if (name == "duplicate")
    {
        Vector3D mod;

        str >> mod;
        a = Construct(str, mem);

        if (a == NULL) throw MakeParserException("Bad object in duplicate.");

        obj = new Duplicate(a, mod);
    }
    else if (name == "matrix")
    {
        Matrix<> matrix;
        
        str >> matrix;
        a = Construct(str, mem);

        obj = new TransRot(a, matrix);
    }
    else if (name == "scale")
    {
        double scale;

        str >> scale;
        a = Construct(str, mem);

        obj = new Scale(a, scale);
    }
    else throw MakeParserException("Bad operation type. Expected one of 'boolean', 'matrix' or 'scale'");

    } catch (ParserException & ex) {
        SAFE_RELEASE(b);
        SAFE_RELEASE(a);
        SAFE_RELEASE(obj);
        throw ex;
    }

    char   rbracket;
    str >> rbracket; 
    if (rbracket != ']') 
    {
        SAFE_RELEASE(b);
        SAFE_RELEASE(a);
        SAFE_RELEASE(obj);
        throw MakeParserException("Expected ']'"); 
    }

    return obj;
}


IObject* ObjectFactory::CreateObject(std::string & name, std::istream & str)
{
    IObject* obj(NULL);

    try
    {
        if (name == "sphere")
        {
            Point4D pos;
            double rad;

            if (!(str >> pos >> rad)) throw MakeParserException("Invalid value for sphere");
            
            obj = new Sphere(pos, rad);
        }
        else if (name == "cube")
        {
            Point4D pos;
            double size;

            if (!(str >> pos >> size)) throw MakeParserException("Invalid value for cube");

            obj = new Box(pos, size);
        }
        else if (name == "box")
        {
            Point4D pos;
            Point4D size;

            if (!(str >> pos >> size)) throw MakeParserException("Invalid value for box");

            obj = new Box(pos, size);
        }
        else if (name == "torus")
        {
            Point4D pos;
            double a, b;

            if (!(str >> pos >> a >> b)) throw MakeParserException("Invalid value for torus");
            
            obj = new Torus(pos, a, b);
        }
        else if (name == "cylinder")
        {
            Point4D pos;
            double rad, size;

            if (!(str >> pos >> rad >> size)) throw MakeParserException("Invalid value for cylinder");

            obj = new Cylinder(pos, rad, size);
        }
        else if (name == "plane")
        {
            Point4D pos, normal;

            if (!(str >> pos >> normal)) throw MakeParserException("Invalid value for plane");

            obj = new Plane(pos, normal);
        }
        else 
        {
            /// lookup in memory or throw exception
            throw MakeParserException(std::string("Unknow object type - ") + name);
        }
    } catch(ParserException & ex)
    {
        SAFE_RELEASE(obj);
        throw ex;
    }

    char   rbracket;
    str >> rbracket; 
    if (rbracket != ']') {
        SAFE_RELEASE(obj);
        throw MakeParserException("Expected ']'"); 
    }

    return obj;
}
