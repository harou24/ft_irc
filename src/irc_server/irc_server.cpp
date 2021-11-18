#include "irc_server.hpp"
#include "../client/ostream_client.hpp"

IrcServer::IrcServer(void) : Server() { }

IrcServer::IrcServer(const char *port) : Server(port) { }

IrcServer::~IrcServer(void) { }

bool    IrcServer::userExists(const std::string &nickName) const
{
    return (this->users.find(nickName) != this->users.end());
}

void    IrcServer::nick(const t_nick &nick)
{
    if (this->Server::getNbConnectedClients() > 0)
    {
        if (!this->userExists(nick.nickName))
        {
            Client c = *(this->Server::getClients()->rbegin()->second);
            IrcClient *cl = new IrcClient(c);
            cl->setNickName(nick.nickName);
            this->users.insert(std::pair<std::string, IrcClient*>(nick.nickName, cl));
       
        }
        else
            this->users[nick.nickName]->setNickName(nick.nickName);
    }
}

void    IrcServer::user(const t_user &user)
{
    std::cout << "USER->" << user.hostName << std::endl; 
}

std::vector<Message*>::iterator   IrcServer::getLastUnreadMsg(void)
{
    std::vector<Message*>::iterator unreadMsg;
    for (unreadMsg = this->getMessages()->begin(); unreadMsg != this->getMessages()->end(); unreadMsg++)
        if (!((*unreadMsg)->hasItBeenRead()))
            break;
    return (unreadMsg);
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
    delete(cmd);
}

void    IrcServer::start(void)
{
    this->TcpConnection::init(TO_LISTEN);
    while (true)
    {
        this->runOnce();
        if (this->getMessages()->size() > 0)
        {
            std::vector<Message*>::iterator unreadMsg;
            for (unreadMsg = this->getMessages()->begin(); unreadMsg != this->getMessages()->end(); unreadMsg++)
                if (!((*unreadMsg)->hasItBeenRead()))
                    this->handleLastReceivedMessage(unreadMsg);
        }
    }
}

std::map<std::string, IrcClient*> IrcServer::getUsers(void) const
{
    return (this->users);
}

