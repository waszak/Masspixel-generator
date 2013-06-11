#include "image.hpp"


std::ostream& Image::serialize(std::ostream& ostr) const
{
	if (ostr.bad())
		throw MakeException("Bad output stream while serializing image");

	ostr.put(0);
	ostr.put(0);
	ostr.put(2); /* RGB without compression */
	ostr.put(0); ostr.put(0);
	ostr.put(0); ostr.put(0);
	ostr.put(0);
	ostr.put(0); ostr.put(0);           /* X origin */
	ostr.put(0); ostr.put(0);           /* Y origin */
	ostr.put((width & 0x00FF));
	ostr.put((width & 0xFF00) / 256);
	ostr.put((height & 0x00FF));
	ostr.put((height & 0xFF00) / 256);
	ostr.put(32);                        /* 32 bits*/
	ostr.put(0);

	ostr.write((char*)rgba, sizeof(uint) * width * height);

	return ostr;
}


std::istream& Image::deserialize(std::istream& istr)
{
	return istr;
}
