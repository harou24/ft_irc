#include "user.hpp"

User::User(void) { }

User::User(std::string &nickName, std::string &userName, std::string &hostName, std::string &serverName)
{
    this->nickName = nickName;
    this->userName = userName;
    this->hostName = hostName;
    this->serverName = serverName;
}

User::~User(void) { }


void            User::setNickName(const std::string &nickName) { this->nickName = nickName; }

std::string     User::getNickName(void) const { return (this->nickName); }
