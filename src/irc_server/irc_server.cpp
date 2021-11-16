#include "irc_server.hpp"
#include "../cmd_parser/cmd_parser.hpp"
#include "../client/ostream_client.hpp"

IrcServer::IrcServer(void) : Server() { }

IrcServer::IrcServer(const char *port) : Server(port) { }

IrcServer::~IrcServer(void) { }

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
            /*
            if (cmd->getType() == NICK)
            {
                t_nick *nick = (t_nick *)cmd->getCmd();
            }
            else if (cmd->getType() == USER)
            {
                t_user *user = (t_user *)cmd->getCmd();
            }
            else if (cmd->getType() == PRIVMSG)
            {
                t_privMsg *privmsg = (t_privMsg *)cmd->getCmd();
            }
            else
            {
                t_unknown *unknown = (t_unknown *)cmd->getCmd();
            }
            */
           delete(cmd);
        }
    }
}

