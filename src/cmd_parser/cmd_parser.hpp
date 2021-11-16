#ifndef CMD_PARSER_HPP
# define CMD_PARSER_HPP

# include "../parser/parser.hpp"

enum e_type
{
    NICK,
    USER,
    PRIVMSG,
    UNKNOWN
};

typedef struct  s_nick
{
    std::string nickName;
}               t_nick;

typedef struct  s_privMsg
{
    std::string nickName;
    std::string msg;
}               t_privMsg;

typedef struct  s_user
{
        std::string userName;
        std::string hostName;
        std::string serverName;
        std::string realName;
}                t_user;

typedef struct  s_unknown
{
    std::string error;
}               t_unknown;

class CmdParser : public Parser {
    
    private:
        e_type      type;
        std::string cmd;
        std::vector<std::string> tokens;
    
    public:
        CmdParser(void);
        CmdParser(const std::string &cmd);
        ~CmdParser(void);

        void        parse(const std::string &cmd);

        e_type      getType(void) const;

        void        setType(void);

        t_nick     getNick(void) const;
        t_user     getUser(void) const;
        t_privMsg  getPrivMsg(void) const;
        t_unknown   getUnknown(void) const;

        std::vector<std::string>        getTokens(void);
};

#endif
