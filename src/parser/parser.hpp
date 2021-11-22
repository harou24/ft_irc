#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <vector>

class Parser {
	private:
        std::string str;
	public:
		Parser(void);
		Parser(const std::string &strToParse);
		~Parser(void);

		std::vector<std::string>  split(void);
		std::vector<std::string>  split(const std::string &str);
		std::vector<std::string>  split(const std::string &str, const char del);
        std::string removeSpaces(const std::string &s) const;
};

#endif
