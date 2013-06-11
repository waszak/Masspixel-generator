#ifndef __ISERIALIZABLE_HPP__
#define __ISERIALIZABLE_HPP__
#include <iostream>
#include <string>

/// Interfejs umozliwiajaca latwiejsza serializacje danych do strumienia pliku/tekstu/czegos innego?
class ISerializable
{
public:
	friend std::ostream& operator<<(std::ostream& ostr, const ISerializable* obj);
	friend std::istream& operator>>(std::istream& istr, ISerializable* obj);
    friend std::ostream& operator<<(std::ostream& ostr, const ISerializable& obj);
	friend std::istream& operator>>(std::istream& istr, ISerializable& obj);

//private: // dlaczegooz to musi byc publiczne?!
	virtual std::ostream& serialize(std::ostream& ostr) const = 0;
	virtual std::istream& deserialize(std::istream& istr) = 0;
};


/// Kilka przydatnych funkcji ulatwiajacych rozne rzeczy z serializacja
namespace Serialize
{
    /// Serializuje obiekt do pliku
    /// \param filename nazwa i sciezka do pliku z rozszerzeniem
    /// \param obj obiekt implementujacy interfejs do serializacji
    /// \param binary czy plik ma byc binarny czy tekstowy
    /// \return false jesli wystapil jakis blad (zly plik, nie udalo sie zserializowac obiektu etc)
    bool SaveAs(std::string filename, const ISerializable *obj, bool binary = true);

    /// Wczytuje zserializowane dane z pliku do obiektu
    /// \param filename nazwa i sciezka pliku z rozszerzeniem
    /// \param obj obiekt implementujacy interfejs do serializacji
    /// \param binary czy plik ma byc odczytywany jako strumien binarny czy tekstowy
    bool LoadFrom(std::string filename, ISerializable *obj, bool binary = true);

    ///////////////////////////////////////////////////////////////

    /// Serializuje obiekt do tekstu
    /// \param obj obiekt implementujacy interfejs do serializacji
    /// \return tekstowy zapis pliku
    std::string ToString(const ISerializable* obj);

    /// Wczytuje obiekt z zapisu tekstowego
    /// \param string_input tekst z zserializowanym obiektem
    /// \param obj obiekt implementujacy interfejs do serializacji
    /// \return false gdy wystapil blad (blad tworzenia obiektu itd)
    bool FromString(std::string string_input, ISerializable* obj);

    void operator>>(const std::string & string_input, ISerializable& obj);
};

#endif //__ISERIALIZABLE_HPP__
