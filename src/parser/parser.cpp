#include "parser.hpp"

#include <string>
#include <sstream>

Parser::Parser(void) { }

Parser::Parser(const std::string &strToParse) : str(strToParse) { }

Parser::~Parser(void) { }

std::vector<std::string>    Parser::split(void) { return (this->split(this->str)); }

std::vector<std::string>    Parser::split(const std::string &str)
{ 
    std::vector<std::string> tokens;
    std::stringstream streamStr(str);
    std::string tmp;
    while (getline(streamStr, tmp, ' '))
        tokens.push_back(tmp);
    return (tokens);
}


