#include "irc_server.hpp"

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
            std::cout << command << std::endl;
            std::string cmd = "PRIVMSG";
            if (command.find(cmd) != std::string::npos)
            {
                std::cout << "PRIVMSG" << std::endl;
            }
                
            
        }
    }
}

