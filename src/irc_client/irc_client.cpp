#include "irc_client.hpp"
#include "../utils/colors.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#define LOGIN_SIZE 20

IrcClient::IrcClient(void) { }

IrcClient::IrcClient(const char *hostName, const char *port) : Client(hostName, port)
{
    this->serverName = std::string(hostName);
    struct passwd *user = this->getUserInfo();
    this->nickName = user->pw_name;
    this->hostName = user->pw_name;
    this->userName = user->pw_name;
    this->realName = user->pw_gecos;
}

IrcClient::IrcClient(std::string &nickName, std::string &userName, std::string &hostName, std::string &serverName)
{
    this->nickName = nickName;
    this->userName = userName;
    this->hostName = hostName;
    this->serverName = serverName;
}

IrcClient::~IrcClient(void) { }

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
    std::string user("USER " + this->nickName + " " + this->hostName + " " + this->serverName + " :" + this->realName + "\n");
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

void            IrcClient::setNickName(const std::string &nickName) { this->nickName = nickName; }

std::string     IrcClient::getNickName(void) const { return (this->nickName); }
