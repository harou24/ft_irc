#include "cmd_parser.hpp"
#include <sstream>

CmdParser::CmdParser(void) { }

CmdParser::CmdParser(const std::string &cmd) : Parser()
{
    this->cmd = cmd;
    this->tokens = this->CmdParser::split(cmd);
    this->setType();
}

CmdParser::~CmdParser(void) { }

std::vector<std::string>    CmdParser::split(const std::string &cmd)
{
    std::vector<std::string> tokens;
    std::stringstream streamStr(cmd);
    std::string tmp;
    while (getline(streamStr, tmp, ' '))
    {
        size_t found = tmp.find(":");
        if (found != std::string::npos)
        {
            std::string lastToken = cmd.substr(cmd.find(":") + 1);
            tokens.push_back(lastToken);
            break ;
        }
        else
        {
            tokens.push_back(tmp);
        }
    }
    return (tokens);
}

void        CmdParser::setType(void)
{
    if (this->cmd.find("NICK") != std::string::npos)
        this->type = NICK;
    else if (this->cmd.find("USER") != std::string::npos)
        this->type = USER;
    else if (this->cmd.find("PRIVMSG") != std::string::npos)
        this->type = PRIVMSG;
    else
        this->type = UNKNOWN;
}

t_nick     CmdParser::getNick(void) const
{
    t_nick nick;
    nick.nickName = tokens[1];
    return (nick);
}

t_user     CmdParser::getUser(void) const
{
    t_user user;
    user.userName = tokens[1];
    user.hostName = tokens[2];
    user.serverName = tokens[3];
    user.realName = tokens[4];
    return (user);
}

t_privMsg     CmdParser::getPrivMsg(void) const
{
    t_privMsg privmsg;
    privmsg.nickName = tokens[1];
    privmsg.msg = tokens[2];
    return (privmsg);
}

t_unknown  CmdParser::getUnknown(void) const
{
    t_unknown unknown;
    unknown.error = std::string("Error cmd does not exist : [ " + this->cmd + " ]");
    return (unknown);
}

e_type      CmdParser::getType(void) const { return this->type; }

std::vector<std::string> CmdParser::getTokens(void) { return (this->tokens); }
