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

std::vector<std::string>    Parser::split(const std::string &str, const char c)
{ 
    std::vector<std::string> tokens;
    std::stringstream streamStr(str);
    std::string tmp;
    while (getline(streamStr, tmp, c))
    {
        std::string str = this->removeSpaces(tmp);
        tokens.push_back(str);
    }
    return (tokens);
}

std::string Parser::removeSpaces(const std::string &s) const
{
  int last = s.size() - 1;
  while (last >= 0 && (s[last] == '\r' || s[last] == ' ' || s[last] == '\n'))
    --last;
  return s.substr(0, last + 1);
}
