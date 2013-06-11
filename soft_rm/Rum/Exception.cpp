#include "exception.hpp"
#include <iostream>

std::ostream & operator <<(std::ostream & ostr, const Exception & ex) {
	ostr << ex.what();
	return ostr;
}
