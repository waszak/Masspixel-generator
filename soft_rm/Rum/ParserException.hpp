#ifndef __PARSER_EXCEPTION_HPP__
#define __PARSER_EXCEPTION_HPP__
#include "Exception.hpp"
#include "utils.hpp"


/// Exception while parsing
/// TODO: add track of line and character number
class ParserException : public Exception
{
public:
    explicit ParserException(std::string error, std::string location) : Exception(error, location), line(0), charnum(0) {}

    int GetLine()         const { return line; }
    int GetCharacterNum() const { return charnum; }

    ParserException& Line(int l) { line = l; return *this; }

    virtual const char* what() const throw() {
        return std::string(std::string(Exception::what()) 
            + std::string("  !It happend on line ") + ToString<>(line) 
            + std::string(" at ") + ToString<>(charnum) + std::string("!.\n")).c_str();
    }
private:
    int line;
    int charnum;
};

#define MakeParserException(WHAT)                           ParserException((WHAT), CODE_LOCATION)

#endif //__PARSER_EXCEPTION_HPP__//
