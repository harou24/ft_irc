#include "cmd_parser.hpp"

CmdParser::CmdParser(void) { }

CmdParser::CmdParser(const std::string &cmd)
{
    std::vector<std::string> tokens = this->split(cmd);
    if (tokens.front() == "PRIVMSG")
    {
        this->cmd = tokens[0];
        this->type = PRIVMSG;
        this->nickName = tokens[1];
        for (size_t i = 2; i < tokens.size(); i++)
        {
            this->msg += tokens[i];
            if (i != tokens.size() - 1)
                this->msg += ' ';
        }
        this->msg.erase(0, 1);
    }
}

CmdParser::~CmdParser(void) { }

void            CmdParser::parse(const std::string &cmd)
{
    std::vector<std::string> tokens = this->split(cmd);
    if (tokens[0] == "PRIVMSG")
    {
        this->cmd = tokens[0];
        this->type = PRIVMSG;
        this->nickName = tokens[1];
        for (size_t i = 2; i < tokens.size(); i++)
        {
            this->msg += tokens[i];
            if (i != tokens.size() - 1)
                this->msg += ' ';
        }
        this->msg.erase(0, 1);
    }
}

std::string     CmdParser::getNickName(void) const { return (this->nickName); }

std::string     CmdParser::getMsg(void) const { return (this->msg); }

std::string     CmdParser::getCmd(void) const { return (this->cmd); }

e_type          CmdParser::getType(void) const { return (this->type); }
