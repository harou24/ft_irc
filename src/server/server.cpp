#include "server.hpp"
#include "../tcp_connection/tcp_utils.hpp"

#include <unistd.h>
#include <arpa/inet.h>

#define WELCOME_MSG "------- Welcome to the server ! -------\n"

Server::Server(void): TcpConnection("8080") { }

Server::Server(const char *port): TcpConnection(port) { }

Server::~Server(void) { }

void    Server::sendGreetingMsg(const Client &cl) const
{
    write(cl.getFd(), WELCOME_MSG, sizeof(WELCOME_MSG));
}

void    Server::handleNewClient(void)
{
    Client cl;
    try 
    {
        this->acceptClientConnection(cl);
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    sendGreetingMsg(cl);
    std::cout << cl;
    this->clients.insert(std::pair<int, Client>(cl.getFd(), cl));
}

Client    Server::getClient(const int fd)
{
    std::map<int, Client>::iterator it;
    it = this->clients.find(fd);
    return(it->second);
}

void    Server::removeClient(const Client &cl)
{
        std::map<int, Client>::iterator it;
        it = this->clients.find(cl.getFd());
        this->clients.erase(it);
}

void    Server::handleClientRemoval(const Client &cl)
{
        close(cl.getFd());
        removeFdFromSet(cl.getFd(), this->getMasterFds());
        this->removeClient(cl);
}

void    Server::handleClientData(const int fd)
{
    std::string data;

    try
    {
        data = this->getDataFromFd(fd);
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    Client cl = this->getClient(fd);
    if (data.empty())
    {
        cl.setConnected(false);
        this->handleClientRemoval(cl);
    }
    else
    {
        cl.setData(data);
    }
    std::cout << cl;
}

void    Server::start(void)
{
    this->init();
    while (true)
    {
        try
        {
            this->updateFdsInSet();
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
        for(int fd = 0; fd <= this->getFdMax(); fd++)
        {

            if (isFdReadyForCommunication(fd))
            {
                if (fd == this->getListenerFd())
                    this->handleNewClient();
                else
                    this->handleClientData(fd);
            }
        }
    }
}
