#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__
#include "Point.hpp"
#include "Color.hpp"
#include "ISerializable.hpp"

/// Represents object's material
struct Material : public ISerializable
{
    Color<double>::type diffuse, ambient, specular, sss;
    bool doSSS;
    double specularHardness;
    double reflection, diff;
    //double emission;

    Material(Color<double>::type diff, Color<double>::type amb, Color<double>::type spec, double h) 
        : diffuse(diff), ambient(amb), specular(spec), specularHardness(h), doSSS(false)
    {}

    Material()
    {
        ambient  = diffuse = NewPoint4D(1.,0.89,0.9, 1.0);
        specular = NewPoint4D(1.,1.,1.);
        specularHardness = 230.;
        sss = NewPoint4D(1.0,0.4,0.4,1.0);
        doSSS = false;
        reflection = 0;
    }

    std::ostream& serialize(std::ostream &str) const
    {
        str << '[' << diffuse << ' ' << specular << ' ' << specularHardness << ' ';
        str << ambient;
        if (doSSS) str << " with-sss" << sss;
        str << ']';

        return str;
    }

    std::istream& deserialize(std::istream &str)
    {
        char z(0);

        str >> z; 
        if (z != '[') 
            throw MakeParserException("Expected '[' for material definition.");

        int i = 0;
        try
        {
            str >> diffuse; ++i;
            str >> specular; ++i;
            str >> specularHardness; ++i;
            str >> ambient; ++i;
        } catch (ParserException &ex) 
        { 
            throw MakeParserException(ex.GetError() + whichFailed(i));
        }

        std::string opt;
        str >> opt;
        if (opt == "with-sss")
        {
            try
            {
                str >> sss;
                doSSS = true;
            }
            catch (ParserException& ex)
            {
                throw MakeParserException(ex.GetError() + "no SSS color.");
            }

            str >> z; 
            if (z != ']') throw MakeParserException("Expected ']' for material.");
        }
        else if (opt != "]") 
            throw MakeParserException("Expected ']' or 'with-sss <color>]' for material. ");

        sss      = vf::clamp(sss);
        diffuse  = vf::clamp(diffuse);
        ambient  = vf::clamp(ambient);
        specular = vf::clamp(specular);

        reflection = diffuse[3];
        diff       = 1. - reflection;
        diffuse[3] = 1;

        return str;
    }

    static std::string whichFailed( int i ) 
    {
        switch(i)
        {
        case 0:
            return " Diffuse color is invalid.";
        case 1:
            return " Specular color is invalid.";
        case 2:
            return " Specular hardness is invalid.";
        case 3:
            return " Ambient color is invalid.";
        default:
            return " Unknown";
        }
    }


};

#endif //__MATERIAL_HPP__
