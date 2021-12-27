#include "irc_server.hpp"
#include "ostream_irc_server.hpp"
#include "../client/ostream_client.hpp"

#include "../tcp_connection/tcp_connection.hpp"
#include "../tcp_connection/tcp_utils.hpp"

#include "../commands/commands.hpp"

#include <unistd.h>
#include <stdlib.h>

IrcServer::IrcServer(void)
    : server(new Server()), isRunning(false), users(new std::map<std::string, IrcClient*>()),
        channels(new std::map<std::string, Channel*>())
{ }

IrcServer::IrcServer(const char *port)
    : server(new Server(port)), isRunning(false), users(new std::map<std::string, IrcClient*>()),
        channels(new std::map<std::string, Channel*>())
{ }

IrcServer::~IrcServer(void)
{
}

bool    IrcServer::userExists(const std::string &nickName) const
{
    return (this->users->find(nickName) != this->users->end());
}

bool    IrcServer::channelExists(const std::string &name) const
{
    return (this->channels->find(name) != this->channels->end());
}

Channel*    IrcServer::getChannel(const std::string &name) const
{
    Channel *channel = NULL;
    if (this->channelExists(name))
        channel = this->channels->find(name)->second;
    return (channel);
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

void        IrcServer::addChannel(const std::string &name, Channel *channel)
{
    this->channels->insert(std::pair<std::string, Channel*>(name, channel));
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
    else if ((*lastMsg)->getCmd().getType() == USER)
        user(this, lastMsg);
    else if ((*lastMsg)->getCmd().getType() == PING)
        reply = pong(this, lastMsg);
    else if ((*lastMsg)->getCmd().getType() == PRIVMSG)
        reply = privMsg(this, lastMsg);
    else if ((*lastMsg)->getCmd().getType() == WHOIS)
        reply = whoIs(this, lastMsg);
//    else if ((*lastMsg)->getCmd().getType() == MODE)
//        reply = userMode(this, lastMsg);
    else if ((*lastMsg)->getCmd().getType() == JOIN)
        reply = join(this, lastMsg);
    else
        reply = unknown(this, lastMsg);
    std::cerr << "REPLY->" << reply << std::endl;
    return (reply);
}

void IrcServer::handleLastReceivedMessage(std::vector<Message*>::iterator lastMsg)
{
    std::string command = (*lastMsg)->getData();
    CmdParser cmd = CmdParser(command);
    cmd.debug();
    std::string reply = this->execCmd(lastMsg);
    if (!reply.empty())
        this->server->sendMsg((*lastMsg)->getSender()->getFd(), reply);
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

void	IrcServer::stop(void)
{
	this->isRunning = false;
	std::cout << "STOPING SERVER...\n";
	//exit(0);
}

void	IrcServer::init(void)
{
    this->server->TcpConnection::init(TcpConnection::TO_LISTEN);
}

void	IrcServer::runOnce(void)
{
        this->server->runOnce();
        this->handleUnreadMessages();
        std::cerr << *this;
}

void    IrcServer::start(void)
{
    this->init();
    this->isRunning = true;
    while (this->isRunning)
        this->runOnce();
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

std::map<std::string, Channel*>* IrcServer::getChannels(void) const
{
    return (this->channels);
}

Server&  IrcServer::getServer(void) const { return (*(this->server)); }

