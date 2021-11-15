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
        std::cout << "Nb Connected->" << this->getNbConnectedClients() << std::endl;
        if (!this->receivedMessages.empty())
        {
            std::string command = this->receivedMessages.back();
            std::cout << "command->" << command << std::endl;
            CmdParser *cmd = new CmdParser(command);
            if (cmd->getType() == PRIVMSG)
            {
                std::cout << "PRIVMSG type->" << cmd->getCmd() << std::endl;
            }
           delete(cmd);
        }
    }
}

