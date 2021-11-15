#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <vector>

class Parser {
	private:
		
	public:
		Parser(void);
		Parser(const std::string &strToParse);
		~Parser(void);

		std::vector<std::string>  strSplit(void);
		std::vector<std::string>  strSplit(std::string &str);



};

#endif
