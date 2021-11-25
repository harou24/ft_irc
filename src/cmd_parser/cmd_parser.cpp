#include "cmd_parser.hpp"
#include "../utils/colors.h"

#include <sstream>
#include <cstdio>

CmdParser::CmdParser(void) : type(UNKNOWN), cmd("default") { }

CmdParser::CmdParser(const std::string &cmd) : Parser(), type(UNKNOWN), cmd("default")
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
            std::remove(tmp.begin(), tmp.end(), ' ');
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
    std::remove(nick.nickName.begin(), nick.nickName.end(), '\n');
    return (nick);
}

t_user     CmdParser::getUser(void) const
{
    t_user user;
    user.userName = this->Parser::removeSpaces(tokens[1]);
    user.hostName = this->Parser::removeSpaces(tokens[2]);
    user.serverName = this->Parser::removeSpaces(tokens[3]);
    user.realName = this->Parser::removeSpaces(tokens[4]);
    std::remove(user.realName.begin(), user.realName.end(), '\n');
    return (user);
}

t_privMsg     CmdParser::getPrivMsg(void) const
{
    t_privMsg privmsg;
    privmsg.nickName = this->Parser::removeSpaces(tokens[1]);
    privmsg.msg = this->Parser::removeSpaces(tokens[2]);
    return (privmsg);
}

t_unknown  CmdParser::getUnknown(void) const
{
    t_unknown unknown;
    unknown.error = std::string("Error cmd does not exist : | " + this->cmd + " |");
    return (unknown);
}

e_type      CmdParser::getType(void) const { return this->type; }

std::vector<std::string> CmdParser::getTokens(void) { return (this->tokens); }

void    CmdParser::debug(void) const
{
    std::cerr << "::CMD_PARSER_DEBUG::" << std::endl;
    std::cerr << RED << "TYPE->" << GREEN;
    if (this->type == NICK)
        std::cerr << "|NICK|";
    else if (this->type == USER)
        std::cerr << "|USER|";
    else if (this->type == PRIVMSG)
        std::cerr << "|PRIVMSG|";
    else
        std::cerr << "|UNKNOWN|";
    std::cerr << RESET << std::endl;
    std::cerr << RED << "CMD->" << GREEN << "|" << this->cmd << "|" << RESET << std::endl;
    for (size_t i = 0; i < this->tokens.size(); i++)
        std::cerr << RED << "tokens[" << i << "]->" << GREEN << "|" << this->tokens[i] << "|" << RESET << std::endl;
}
