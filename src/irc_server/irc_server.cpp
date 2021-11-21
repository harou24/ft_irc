#include "irc_server.hpp"
#include "ostream_irc_server.hpp"
#include "../tcp_connection/tcp_connection.hpp"
#include "../client/ostream_client.hpp"
#include <stdio.h>
IrcServer::IrcServer(void) : server(new Server()), users(new std::map<std::string, IrcClient*>()) { }

IrcServer::IrcServer(const char *port) : server(new Server(port)), users(new std::map<std::string, IrcClient*>()) { }

IrcServer::~IrcServer(void) { }

bool    IrcServer::userExists(const std::string &nickName) const
{
    return(this->users->find(nickName) != this->users->end());
}

bool IrcServer::isClientUser(const Client &cl) const
{
    std::map<std::string, IrcClient*>::iterator it;
    for (it = this->users->begin(); it != this->users->end(); it++)
    {
        if (it->second->getFd() == cl.getFd() && !it->second->getUserName().empty())
            return (true);
    }
    return (false);
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
    }
}

void    IrcServer::handleLastReceivedMessage(std::vector<Message*>::iterator lastMsg )
{
    std::string command = (*lastMsg)->getData();
    CmdParser *cmd = new CmdParser(command);
    if (cmd->getType() == NICK)
    {
        t_nick nick = cmd->getNick();
        this->nick(nick);
    }
    else if (cmd->getType() == USER)
    {
        t_user user = cmd->getUser();
        this->user(user);
    }
    
    else if (cmd->getType() == PRIVMSG)
    {
        t_privMsg privMsg = cmd->getPrivMsg();
        privMsg.msg = privMsg.msg ;
    }
    else
    {
        t_unknown unknown = cmd->getUnknown();
        unknown.error = unknown.error;
    }
    (*lastMsg)->setRead(true);
    delete(cmd);
}

void    IrcServer::start(void)
{
    server->TcpConnection::init(TcpConnection::TO_LISTEN);
    while (true)
    {
        server->runOnce();
        if (server->getMessages()->size() > 0)
        {
            std::vector<Message*>::iterator unreadMsg;
            for (unreadMsg = server->getMessages()->begin(); unreadMsg != server->getMessages()->end(); unreadMsg++)
                if (!((*unreadMsg)->hasItBeenRead()))
                    this->handleLastReceivedMessage(unreadMsg);
        }
      std::cout << *this;
    }
}

std::map<std::string, IrcClient*>* IrcServer::getUsers(void) const
{
    return (this->users);
}

Server  IrcServer::getServer(void) const { return (*(this->server)); }

