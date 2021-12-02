#include "irc_server.hpp"
#include "ostream_irc_server.hpp"
#include "../client/ostream_client.hpp"

#include "../tcp_connection/tcp_connection.hpp"
#include "../tcp_connection/tcp_utils.hpp"

#include "../commands/commands.hpp"

#include <unistd.h>

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
        if (it->second->getClient()->getFd() == fd)
            usr = it->second;
    }
    return (usr);
}

void        IrcServer::addUser(const std::string &nickName, IrcClient *cl)
{
    this->users->insert(std::pair<std::string, IrcClient*>(nickName, cl));
}

IrcClient*        IrcServer::removeUser(const std::string &nickName)
{
    IrcClient *cl = this->users->find(nickName)->second;
    this->users->erase(this->users->find(nickName));
    return (cl);
}

bool    IrcServer::isNickInUse(const std::string &nickName)
{
    return (this->users->find(nickName) != this->users->end());
}

std::string IrcServer::execCmd(std::vector<Message*>::iterator lastMsg)
{
    std::string reply;
    if ((*lastMsg)->getCmd().getType() == NICK)
        reply = nick(this, lastMsg);
    /*
    else if ((*lastMsg)->getCmd().getType() == USER)
        user(this, lastMsg);
    else if ((*lastMsg)->getCmd().getType() == PING)
        reply = pong(this, lastMsg);
    else if ((*lastMsg)->getCmd().getType() == PRIVMSG)
        reply = privMsg(this, lastMsg);
    else if ((*lastMsg)->getCmd().getType() == WHOIS)
        reply = whoIs(this, lastMsg);
    else if ((*lastMsg)->getCmd().getType() == MODE)
        reply = userMode(this, lastMsg);
    else
        reply = unknown(this, lastMsg);
    std::cerr << "REPLY->" << reply << std::endl;*/
    return (reply);
}

void IrcServer::handleLastReceivedMessage(std::vector<Message*>::iterator lastMsg)
{
    std::string command = (*lastMsg)->getData();
    CmdParser cmd = CmdParser(command);
    cmd.debug();
    std::string reply = this->execCmd(lastMsg);
    if (!reply.empty())
        this->server->sendMsg((*lastMsg)->getSender().getFd(), reply);
    (*lastMsg)->setRead(true);
}

void    IrcServer::handleUnreadMessages(void)
{
    if (server->getMessages()->size() > 0)
    {
        std::vector<Message*>::iterator unreadMsg = server->getMessages()->begin();
        std::vector<Message*>::iterator msgEnd = server->getMessages()->end();
        while (unreadMsg != msgEnd)
        {
            if (!((*unreadMsg)->hasItBeenRead()))
            {
                this->handleLastReceivedMessage(unreadMsg);
            }
            unreadMsg++;
        }
    }
}

void    IrcServer::start(void)
{
    this->server->TcpConnection::init(TcpConnection::TO_LISTEN);
    while (true)
    {
        this->server->runOnce();
        this->handleUnreadMessages();
        std::cerr << *this;
    }
}

void    IrcServer::removeClientWithReply(const Client *cl, const std::string &reply)
{
    this->server->sendMsg(cl->getFd(), reply);
    this->server->handleClientRemoval(cl);
}

std::map<std::string, IrcClient*>* IrcServer::getUsers(void) const
{
    return (this->users);
}

Server&  IrcServer::getServer(void) const { return (*(this->server)); }

