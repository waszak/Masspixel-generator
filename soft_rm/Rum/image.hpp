#ifndef __IMAGE_TGA_HPP__
#define __IMAGE_TGA_HPP__
#include "utils.hpp"
#include "Color.hpp"
#include "Exception.hpp"
#include "ISerializable.hpp"

typedef unsigned int uint;

class Image : public ISerializable
{
public:
	Image(uint w = 0, uint h = 0) {
		rgba = NULL;
		Create(w,h);
	}

	/// Tworzy obrazek w pamieci o zadanych wymiarach
	/// \param w szerokosc obrazka
	/// \param h wysokosc obrazka
	/// \warn Rzuca wyjatkiem gdy nie uda sie zaalokowac pamieci
	void Create(uint w, uint h) {
		width  = w;
		height = h;
		allocate(w,h);
	}

	void Blank(uint c = 0) { memset(rgba, c, sizeof(uint) * width * height); }
	/// Zwraca referencje do piksela w formacie BGRA (8 bitow na kolor)
	uint& operator()(uint x, uint y) {	return rgba[y * width + x]; }
	
    uint Width() const { return width; }
	uint Height() const { return height; }

    uint* Raw() { return rgba; }
    const uint* Raw() const { return rgba; }

private:
	virtual std::ostream& serialize(std::ostream& ostr)   const;
	virtual std::istream& deserialize(std::istream& istr);

	void allocate(uint w, uint h)
	{
		if (rgba != NULL) delete[] rgba;
		try {
			rgba = new uint[w * h * sizeof(uint)];
		} catch (std::bad_alloc& bd) {
			throw MakeException(std::string("Can't allocate memory for image - ") + bd.what());
		}
	}

	uint width, height;
	uint *rgba;
};

#endif //__IMAGE_TGA_HPP__
