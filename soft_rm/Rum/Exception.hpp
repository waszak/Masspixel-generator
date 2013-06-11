#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__
#include <string>
#include <exception>

#define STRINGIFY(X) #X
#define TO_STRING(X) STRINGIFY(X)
#define CODE_LOCATION (__FILE__ ":" TO_STRING(__LINE__))

class Exception;

/// Wypisuje do strumienia informacje o wyjatku
/// \param ostr strumien wyjsciowy
/// \param ex wyjatek
/// \return referencja na zmodyfikowany strumien wyjsciowy
std::ostream & operator <<(std::ostream & ostr, const Exception & ex);


/// Wlasna klasa wyjatkow, posiadajaca dodatkowy opis oraz lokacje rzucenia wyjatku
class Exception : public std::exception
{
public:
	explicit Exception(std::string error, std::string location ) : desc(error), loc(location) {}

	const std::string &GetError() const { return desc; }
	const std::string &GetLocation() const { return loc; }

	virtual const char * what() const throw() { 
		return (std::string("\nException: ") + desc + std::string("\nLocation: ") + loc + std::string("\n")).c_str();
	}

	friend std::ostream & operator <<(std::ostream & ostr, const Exception & ex);

private:
	const std::string desc, loc;
};

#define MakeException(X) Exception((X), CODE_LOCATION)

#endif //__EXCEPTION_HPP__
