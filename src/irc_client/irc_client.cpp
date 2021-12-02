#include "irc_client.hpp"
#include "../utils/colors.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

#define LOGIN_SIZE 20


IrcClient::IrcClient(void) { }

IrcClient::IrcClient(Client *cl, const std::string &nickName) 
{ 
    this->cl = cl;
    this->nickName = nickName;
}

IrcClient::~IrcClient(void) { }

void            IrcClient::setNickName(const std::string &nickName)
{
    this->nickName = nickName;
}

void            IrcClient::setUserName(const std::string &userName)
{
    this->userName = userName;
}

void            IrcClient::setHostName(const std::string &hostName)
{
    this->hostName = hostName;
}

void            IrcClient::setServerName(const std::string &serverName)
{
    this->serverName = serverName;
}

void            IrcClient::setRealName(const std::string &realName)
{
    this->realName = realName;
}

std::string     IrcClient::getNickName(void) const { return (this->nickName); }

std::string     IrcClient::getUserName(void) const { return (this->userName); }

std::string     IrcClient::getHostName(void) const { return (this->hostName); }

std::string     IrcClient::getServerName(void) const { return (this->serverName); }

std::string     IrcClient::getRealName(void) const { return (this->realName); }

const Client&     IrcClient::getClient(void) const { return (*(this->cl)); }

Client*     IrcClient::getClient(void) { return (this->cl); }

void            IrcClient::debug(void) const
{
    std::cerr << "::IRC_CLIENT_DEBUG::" << std::endl;
    if (this->cl->isConnected())
        std::cerr << RED << "STATUS->" << GREEN << "|connected|" << RESET << std::endl;
    else
        std::cerr << RED << "STATUS->" << RED << "|disconnected|" << RESET << std::endl;
    std::cerr << RED << "FD->" << GREEN << "|" << this->cl->getFd() << "|" << RESET << std::endl;
    std::cerr << RED << "IP->" << GREEN << "|" << this->cl->getIp() << "|" << RESET << std::endl;
    std::cerr << RED << "DATA_SENT->" << GREEN << "|" << this->cl->getData() << "|" << RESET << std::endl;
    std::cerr << RED << "NICKNAME->" << GREEN << "|" << this->nickName << "|" << RESET << std::endl;
    std::cerr << RED << "USERNAME->" << GREEN << "|" << this->userName << "|" << RESET << std::endl;
    std::cerr << RED << "HOSTNAME->" << GREEN << "|" << this->hostName << "|" << RESET << std::endl;
    std::cerr << RED << "SERVERNAME->" << GREEN << "|" << this->serverName << "|" << RESET << std::endl;
    std::cerr << RED << "REALNAME->" << GREEN << "|" << this->realName << "|" << RESET << std::endl;
}
