#include "irc_server.hpp"
#include "../client/ostream_client.hpp"

IrcServer::IrcServer(void) : Server() { }

IrcServer::IrcServer(const char *port) : Server(port) { }

IrcServer::~IrcServer(void) { }

void    IrcServer::nick(const t_nick &nick)
{
    if (this->Server::getNbConnectedClients() > 0 && this->Server::getClients()->size() > 0)
    {
        Client *c = this->Server::getClients()->at(5);
        IrcClient *cl = reinterpret_cast<IrcClient*>(c);
        std::cout << cl << "==" << c << std::endl;
        std::cout << "CLIENT->" << *c<< std::endl;
        std::cout << "IRC_CLIENT->" << *cl<< std::endl;
        this->users.insert(std::pair<std::string, IrcClient*>(nick.nickName, cl));
    }
    std::cout << "NICK->" << nick.nickName << std::endl;
}

void    IrcServer::start(void)
{
    this->TcpConnection::init(TO_LISTEN);
    while (true)
    {
        this->runOnce();
        if (!this->receivedMessages.empty())
        {
            std::string command = this->receivedMessages.back();
            CmdParser *cmd = new CmdParser(command);
            if (cmd->getType() == NICK)
            {
                t_nick nick = cmd->getNick();
                this->nick(nick);
            }
            else if (cmd->getType() == USER)
            {
                t_user user = cmd->getUser();
                std::cout << "USER->" << user.userName << std::endl;
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
    }
}

