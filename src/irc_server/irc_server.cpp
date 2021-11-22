#include "irc_server.hpp"
#include "ostream_irc_server.hpp"
#include "../client/ostream_client.hpp"

#include "../tcp_connection/tcp_connection.hpp"

IrcServer::IrcServer(void)
    : server(new Server()), users(new std::map<std::string, IrcClient*>()) { }

IrcServer::IrcServer(const char *port)
    : server(new Server(port)), users(new std::map<std::string, IrcClient*>()) { }

IrcServer::~IrcServer(void) { }

bool    IrcServer::userExists(const std::string &nickName) const
{
    return(this->users->find(nickName) != this->users->end());
}

IrcClient*  IrcServer::getUserByFd(const int fd)
{

    IrcClient *usr = NULL;
    std::map<std::string, IrcClient*>::iterator it;
    for (it = this->users->begin(); it != this->users->end(); it++)
    {
        if (it->second->getFd() == fd)
            usr = it->second;
    }
    return (usr);
}

void    IrcServer::nick(const t_nick &nick)
{
        Client c = *(server->getClients()->rbegin()->second);
        std::cerr  << c << std::endl;
        IrcClient *cl = getUserByFd(c.getFd());
        if (cl == NULL)
        {
            cl = new IrcClient(c);
            cl->setNickName(nick.nickName);
            this->users->insert(std::pair<std::string, IrcClient*>(nick.nickName, cl));
        }
        else
        {
            cl->setNickName(nick.nickName);
        }
        std::cerr << "function nick() DEBUG:\n";
        cl->debug();
}

void    IrcServer::user(const t_user &user)
{
    Client c = *(server->getClients()->rbegin()->second);
    IrcClient *cl = this->getUserByFd(c.getFd());
    if (cl)
    {
        cl->setUserName(user.userName);
        cl->setHostName(user.hostName);
        cl->setServerName(user.serverName);
        cl->setRealName(user.realName);
        std::cerr << "function user() DEBUG:\n";
        cl->debug();
    }
}

void    IrcServer::handleLastReceivedMessage(std::vector<Message*>::iterator lastMsg )
{
    std::string command = (*lastMsg)->getData();
    std::cerr << RED << "CMD->" << GREEN << command << RESET << std::endl;
    CmdParser cmd = CmdParser(command);
    cmd.debug();
    if (cmd.getType() == NICK)
    {
        t_nick nick = cmd.getNick();
        std::cerr << RED;
        std::cerr << "NICK->" << GREEN << nick.nickName << RESET << std::endl;
        this->nick(nick);
    }
    else if (cmd.getType() == USER)
    {
        t_user user = cmd.getUser();
        std::cerr << RED << "USER->" << GREEN << user.userName << RESET << std::endl;
        std::cerr << RED << "USER->" << GREEN << user.hostName << RESET << std::endl;
        std::cerr << RED << "USER->" << GREEN << user.serverName << RESET << std::endl;
        std::cerr << RED << "USER->" << GREEN << user.realName << RESET << std::endl;
        this->user(user);
    }
    
    else if (cmd.getType() == PRIVMSG)
    {
        t_privMsg privMsg = cmd.getPrivMsg();
        privMsg.msg = privMsg.msg ;
    }
    else
    {
        t_unknown unknown = cmd.getUnknown();
        unknown.error = unknown.error;
    }
    (*lastMsg)->setRead(true);
}

void    IrcServer::start(void)
{
    server->TcpConnection::init(TcpConnection::TO_LISTEN);
    while (true)
    {
        server->runOnce();
        if (server->getMessages()->size() > 0)
        {
            std::vector<Message*>::iterator unreadMsg = server->getMessages()->begin();
            std::vector<Message*>::iterator msgEnd = server->getMessages()->end();
            while (unreadMsg != msgEnd)
            {
                if (!((*unreadMsg)->hasItBeenRead()))
                    this->handleLastReceivedMessage(unreadMsg);
                unreadMsg++;
            }
        }
      std::cout << *this;
    }
}

std::map<std::string, IrcClient*>* IrcServer::getUsers(void) const
{
    return (this->users);
}

const Server&  IrcServer::getServer(void) const { return (*(this->server)); }

