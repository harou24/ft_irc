#ifndef CMD_PARSER_HPP
# define CMD_PARSER_HPP

# include "../parser/parser.hpp"

enum e_type
{
    NICK,
    USER,
    PRIVMSG,
    UKNOWN
};

class CmdParser : public Parser {
    private:
        e_type      type;
        std::string cmd;
        std::string nickName;
        std::string msg;
    public:
        CmdParser(void);
        CmdParser(const std::string &cmd);
        ~CmdParser(void);

        void        parse(const std::string &cmd);

        std::string getNickName(void) const;
        std::string getMsg(void) const;
        std::string getCmd(void) const;
        e_type      getType(void) const;


};

#endif
