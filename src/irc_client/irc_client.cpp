#include "irc_client.hpp"
#include "../utils/colors.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

#define LOGIN_SIZE 20

IrcClient::IrcClient(void) : Client(), nickName("default"),
    userName("default"), hostName("default"), serverName("default"), realName("default")
{ }

IrcClient::IrcClient(const char *hostName, const char *port) :
    Client(hostName, port), nickName("default"),
    userName("default"), hostName("default"), serverName("default"), realName("default")
{
    this->serverName = std::string(hostName);
    struct passwd *user = this->getUserInfo();
    this->nickName = user->pw_name;
    this->hostName = user->pw_name;
    this->userName = user->pw_name;
    this->realName = user->pw_gecos;
}

IrcClient::IrcClient(std::string &nickName,
                        std::string &userName,
                            std::string &hostName,
                                std::string &serverName) :
    Client()
{
    this->nickName = nickName;
    this->userName = userName;
    this->hostName = hostName;
    this->serverName = serverName;
}

IrcClient::IrcClient(const IrcClient &cl ) : Client(cl)
{ 
    this->nickName = cl.nickName;
    this->userName = cl.userName;
    this->hostName = cl.hostName;
    this->serverName = cl.serverName;
}

IrcClient::IrcClient(const Client &cl ) : Client(cl) { }

IrcClient::~IrcClient(void) { }

IrcClient& IrcClient::operator = (const IrcClient &cl)
{
    this->setConnected(cl.isConnected());
    this->setFd(cl.getFd());
    this->setIp(cl.getIp());
    this->setData(cl.getData());
    this->nickName = cl.nickName;
    this->userName = cl.userName;
    this->hostName = cl.hostName;
    this->serverName = cl.serverName;
    this->realName = cl.realName;
    return (*this);
}

struct passwd*  IrcClient::getUserInfo(void)
{
    char    login[LOGIN_SIZE];
    memset(login, 0, LOGIN_SIZE);
    getlogin_r(login, LOGIN_SIZE) ;
    return (getpwnam(login));
}

void            IrcClient::connectToServer(void)
{
    this->init(TO_CONNECT);
    std::string nick("NICK " + this->nickName + "\n");
    this->sendMsg(this->getServerFd(), nick);
    std::string user("USER " + this->nickName + " "
                                + this->hostName + " " 
                                    + this->serverName 
                                        + " :" + this->realName + "\n");
    this->sendMsg(this->getServerFd(), user);
}

void            IrcClient::runCommunicationWithServer(void)
{
    while (true)
    {
        std::string data = receiveMsg(this->getServerFd());
        if (!data.empty())
            std::cout << data << std::endl;
        std::cout << GREEN << this->nickName << ":> " << RESET;
        for (std::string line; std::getline(std::cin, line);)
        {
            if (line == "/quit")
            {
                close(this->getServerFd());
                exit(EXIT_SUCCESS);
            }
            std::cout << line << std::endl;
            this->sendMsg(this->getServerFd(), line);
            std::cout << GREEN << "User:> " << RESET;
        }
    }
}

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

void            IrcClient::debug(void) const
{
    std::cerr << "::IRC_CLIENT_DEBUG::" << std::endl;
    if (this->isConnected())
        std::cerr << RED << "STATUS->" << GREEN << "|connected|" << RESET << std::endl;
    else
        std::cerr << RED << "STATUS->" << RED << "|disconnected|" << RESET << std::endl;
    std::cerr << RED << "FD->" << GREEN << "|" << this->getFd() << "|" << RESET << std::endl;
    std::cerr << RED << "IP->" << GREEN << "|" << this->getIp() << "|" << RESET << std::endl;
    std::cerr << RED << "DATA_SENT->" << GREEN << "|" << this->getData() << "|" << RESET << std::endl;
    std::cerr << RED << "NICKNAME->" << GREEN << "|" << this->nickName << "|" << RESET << std::endl;
    std::cerr << RED << "USERNAME->" << GREEN << "|" << this->userName << "|" << RESET << std::endl;
    std::cerr << RED << "HOSTNAME->" << GREEN << "|" << this->hostName << "|" << RESET << std::endl;
    std::cerr << RED << "SERVERNAME->" << GREEN << "|" << this->serverName << "|" << RESET << std::endl;
    std::cerr << RED << "REALNAME->" << GREEN << "|" << this->realName << "|" << RESET << std::endl;
}
