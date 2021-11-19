#include "irc_server.hpp"
#include "ostream_irc_server.hpp"
#include "../tcp_connection/tcp_connection.hpp"
#include "../client/ostream_client.hpp"

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
    {   std::cout << "FD->" << cl.getFd() << std::endl;
        if (it->second->getFd() == cl.getFd())
            return (true);
    }
    return (false);
}

void    IrcServer::nick(const t_nick &nick)
{
    if (server->getNbConnectedClients() > 0)
    {
        Client c = *(server->getClients()->rbegin()->second);
        if (!isClientUser(c))
        {
            IrcClient *cl = new IrcClient(c);
            cl->setNickName(nick.nickName);
            this->users->insert(std::pair<std::string, IrcClient*>(nick.nickName, cl));
        }
    }
    else
        this->users->find(nick.nickName)->second->setNickName(nick.nickName);
}

void    IrcServer::user(const t_user &user)
{
    std::cout << "USER->" << user.hostName << std::endl; 
}

void    IrcServer::handleLastReceivedMessage(std::vector<Message*>::iterator lastMsg )
{
    std::string command = (*lastMsg)->getData();
    std::cout << "LAST MSG->" << command << std::endl;
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
        std::cout << "PRIVMSG->" << privMsg.msg << std::endl;
    }
    else
    {
        t_unknown unknown = cmd->getUnknown();
        std::cout << "UNKNOWN->" << unknown.error << std::endl;
    }
    (*lastMsg)->setRead(true);
    delete(cmd);
}

void    IrcServer::start(void)
{
    server->TcpConnection::init(TcpConnection::TO_LISTEN);
    while (true)
    {
        std::cout << *this;
        server->runOnce();
        if (server->getMessages()->size() > 0)
        {
            std::vector<Message*>::iterator unreadMsg;
            for (unreadMsg = server->getMessages()->begin(); unreadMsg != server->getMessages()->end(); unreadMsg++)
                if (!((*unreadMsg)->hasItBeenRead()))
                    this->handleLastReceivedMessage(unreadMsg);
        }
    }
}

std::map<std::string, IrcClient*>* IrcServer::getUsers(void) const
{
    return (this->users);
}

Server* IrcServer::getServer(void) const { return (this->server); }

