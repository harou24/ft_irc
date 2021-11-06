#include "server.hpp"
#include "server_utils.hpp"

#include <unistd.h>
#include <arpa/inet.h>

Server::Server(void): TcpConnection("8080") { }

Server::Server(const char *port): TcpConnection(port) { }

Server::~Server(void) { }

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
    write(cl.getFd(), "HelloFromServer\n", 17);
    std::cout << cl;
    this->clients.insert(std::pair<int, Client>(cl.getFd(), cl));
}

Client    Server::getClient(int fd)
{
    std::map<int, Client>::iterator it;
    it = this->clients.find(fd);
    return(it->second);
}

void    Server::removeClient(Client cl)
{
        std::map<int, Client>::iterator it;
        it = this->clients.find(cl.getFd());
        this->clients.erase(it);
}

void    Server::handleClientRemoval(Client cl)
{
        close(cl.getFd());
        removeFdFromSet(cl.getFd(), this->getMasterFds());
        this->removeClient(cl);
}

void    Server::handleClientData(int fd)
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
        cl.setDataBuffer(data);
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

            if (isFdInSet(fd, this->getReadFds()))
            {
                if (fd == this->getListenerFd())
                    this->handleNewClient();
                else
                    this->handleClientData(fd);
            }
        }
    }
}
