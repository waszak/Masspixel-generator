#include "Light.hpp"

std::istream& Light::deserialize(std::istream& str)
{
    char z;

    if (!(str >> z) || z != '[') 
    {
        throw MakeParserException("Expected light definition starting with'['.\n").Line(666);
    }
    
    int i = 0;
    try
    {
    	str >> mPosition; ++i;
        str >> mColor;    ++i;
    }
    catch (ParserException& e)
    {
        switch (i)
        {
        case 0: throw MakeParserException("Invalid position for light. " + e.GetError());
        case 1: throw MakeParserException("Invalid color for light." + e.GetError());
        default:
            break; // didn't happen
        }
    }

    if (!(str >> mPower)) throw MakeParserException("Expected double value for Light::mPower");
    
    if (!(str >> z) || z != ']') 
    {
        throw MakeParserException("Expected ']' in light definition.");
    }

    return str;
}


std::ostream& Light::serialize(std::ostream& str) const
{
    str << "[ " << mPosition << " " << mColor << " " << mPower << " ] ";
    return str;
}
