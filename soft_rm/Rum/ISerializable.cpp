#include "ISerializable.hpp"
#include <fstream>
#include <cassert>
#include <sstream>
#include "Exception.hpp"


std::ostream& operator<<(std::ostream& ostr, const ISerializable* obj)
{
	assert(obj != NULL);
	return obj->serialize(ostr);
}


std::istream& operator>>(std::istream& istr, ISerializable* obj)
{
	assert(obj != NULL);
	return obj->deserialize(istr);
}

std::ostream& operator<<(std::ostream& ostr, const ISerializable& obj)
{
	return obj.serialize(ostr);
}


std::istream& operator>>(std::istream& istr, ISerializable& obj)
{
	return obj.deserialize(istr);
}

namespace Serialize
{

bool SaveAs(std::string filename, const ISerializable *obj, bool binary)
{
	std::fstream file;

	file.open(filename.c_str(), (binary? std::ios_base::binary | std::ios_base::out : std::ios_base::out));
	
	if (!file.good()) {
        std::cerr << "Blad odczytu pliku \"" << filename << "\"\n";
        return false;
    }
	
	try
	{
		file << obj;
        file.close();
	} catch (Exception & ex) {
		std::cerr << "Ojejciu! Serializacja obiektu do pliku " << filename << "spowodowala wyjatek: \n" << ex.what();
		return false;
	}

	return true;
}


bool LoadFrom(std::string filename, ISerializable *obj, bool binary)
{
    std::fstream file;

    file.open(filename.c_str(), (binary? std::ios_base::binary | std::ios_base::in : std::ios_base::in));

    if (!file.good()) {
        std::cerr << "Blad odczytu pliku \"" << filename << "\"\n";
        return false;
    }

    try
    {
        file >> obj;
        file.close();
    } catch(Exception & ex)
    {
        std::cerr << "Ojejciu! Blad odczytu z pliku \"" << filename << "\", rzucony wyjatek:\n" << ex.what();
        return false;
    }

    return true;
}


std::string ToString(const ISerializable* obj)
{
    std::stringstream ss;

    try
    {
        ss << obj;
    } catch (Exception &ex)
    {
        std::cerr << "Ojejciu! Blad podczas serializacji obiektu do tekstu - rzucony wyjatek:\n" << ex.what();
    }

    return ss.str();
}


bool FromString(std::string string_input, ISerializable* obj)
{
    std::stringstream ss(string_input);
    
    try
    {
        ss >> obj;
    } catch(Exception & ex)
    {
        std::cerr << "Ojejciu! Blad odczytu z tekstu, rzucony wyjatek:\n" << ex.what();
        return false;
    }

    return true;
}

void operator>>(const std::string & string_input, ISerializable& obj)
{
    std::stringstream ss(string_input);
    ss >> obj;
}

};
