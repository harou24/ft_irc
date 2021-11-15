#include "parser.hpp"

#include <string>
#include <sstream>

Parser::Parser(void) { }

Parser::Parser(const std::string &strToParse) : str(strToParse) { }

Parser::~Parser(void) { }

std::vector<std::string>    Parser::strSplit(void) { return (this->strSplit(this->str)); }

std::vector<std::string>    Parser::strSplit(std::string &str)
{ 
    std::vector<std::string> tokens;
    std::stringstream streamStr(str);
    std::string tmp;
    while (getline(streamStr, tmp, ' '))
        tokens.push_back(tmp);
    return (tokens);
}


