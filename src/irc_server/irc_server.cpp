#include "irc_server.hpp"
#include "ostream_irc_server.hpp"
#include "../client/ostream_client.hpp"

#include "../tcp_connection/tcp_connection.hpp"
#include "../tcp_connection/tcp_utils.hpp"

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

std::string    IrcServer::nick(const CmdParser &cmd)
{
        std::string reply;
        t_nick nick = cmd.getNick();
        Client *c = server->getClients()->rbegin()->second;
        if (!c)
        {
            return (reply);
        }
        IrcClient *cl = getUserByFd(c->getFd());
        if (cl == NULL)
        {
            reply = ":" + getHostName() + " 001 " + nick.nickName + " :welcome to irc server :)\n";
            cl = new IrcClient(*c);
            this->users->insert(std::pair<std::string, IrcClient*>(nick.nickName, cl));
        }
        else
        {
            reply = ":" + cl->getNickName() + " NICK " + nick.nickName + "\n";
        }
        cl->setNickName(nick.nickName);
        return (reply);
}

std::string    IrcServer::user(const CmdParser &cmd)
{
    std::string reply;
    t_user user = cmd.getUser();
    Client c = *(server->getClients()->rbegin()->second);
    IrcClient *cl = this->getUserByFd(c.getFd());
    if (cl)
    {
        cl->setUserName(user.userName);
        cl->setHostName(user.hostName);
        cl->setServerName(user.serverName);
        cl->setRealName(user.realName);
    }
    return (reply);
}

std::string    IrcServer::userMode(const CmdParser &cmd)
{
    std::string reply;
    t_userMode userMode = cmd.getUserMode();
    if (this->users->find(userMode.nickName) != this->users->end())
    {
        reply = "MODE " + userMode.nickName + " " + userMode.mode + "\n";
    }
    return (reply);
}

std::string     IrcServer::pong(const CmdParser &cmd)
{
    t_ping ping = cmd.getPing();
    std::string reply;
    Client c = *(server->getClients()->rbegin()->second);
    IrcClient *cl = this->getUserByFd(c.getFd());
    if (!cl)
        return (reply);
    reply = "PONG " + ping.hostName + "\n";
    return (reply);
}

std::string IrcServer::privMsg(const CmdParser &cmd)
{
    std::string reply;
    t_privMsg privMsg = cmd.getPrivMsg();
    return (reply);
}

std::string IrcServer::unknown(const CmdParser &cmd)
{
    std::string reply;
    t_unknown unknown = cmd.getUnknown();
    reply.assign(unknown.error);
    return (reply);
}

std::string IrcServer::execCmd(const CmdParser &cmd)
{
    std::string reply;
    if (cmd.getType() == NICK)
        reply = this->nick(cmd);
    else if (cmd.getType() == USER)
        this->user(cmd);
    else if (cmd.getType() == MODE)
        this->userMode(cmd);
    else if (cmd.getType() == PING)
        reply = this->pong(cmd);
    else if (cmd.getType() == PRIVMSG)
        reply = this->privMsg(cmd);
    else
        reply = this->unknown(cmd);
    return (reply);
}

void    IrcServer::handleLastReceivedMessage(std::vector<Message*>::iterator lastMsg )
{
    std::string command = (*lastMsg)->getData();
    CmdParser cmd = CmdParser(command);
    cmd.debug();
    std::string reply = this->execCmd(cmd);
    if (!reply.empty())
        this->server->sendMsg((*lastMsg)->getSender()->getFd(), reply);
    (*lastMsg)->setRead(true);
}

void    IrcServer::updateUsersStatus(void)
{
    std::map<std::string, IrcClient*>::iterator it;
    for (it = this->users->begin(); it != this->users->end(); it++)
        if (this->server->getClients()->find(it->second->getFd()) ==
                                        this->server->getClients()->end())
        {
            it->second->setConnected(false);
            std::cout << "Connection lost with -> " << RED << it->second->getNickName() << RESET << "\n\n";
        }
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
                this->handleLastReceivedMessage(unreadMsg);
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
        this->updateUsersStatus();
        this->handleUnreadMessages();
        std::cerr << *this;
    }
}

std::map<std::string, IrcClient*>* IrcServer::getUsers(void) const
{
    return (this->users);
}

const Server&  IrcServer::getServer(void) const { return (*(this->server)); }

