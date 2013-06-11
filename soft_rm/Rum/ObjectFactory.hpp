#ifndef __OBJECT_OBJECTFACTORY_HPP__
#define __OBJECT_OBJECTFACTORY_HPP__
#include <string>
#include "ISerializable.hpp"

class IObject;
class Memory;

class ObjectFactory
{
public:
    static IObject* Construct  (const std::string & objDesc, Memory* mem);
    static IObject* Construct  (std::istream & istr, Memory* mem);
private:
    static IObject* CreateObject   (std::string & name, std::istream & istr);
    static IObject* CreateModifier (std::string & name, std::istream & istr, Memory* mem);
};

#endif //__OBJECT_OBJECTFACTORY_HPP__//
