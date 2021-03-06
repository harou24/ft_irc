#include "server.hpp"
#include "../tcp_connection/tcp_utils.hpp"
#include "../tcp_connection/tcp_exceptions.hpp"
#include "../client/ostream_client.hpp"

#include <unistd.h>
#include <arpa/inet.h>


#define WELCOME_MSG "------- Welcome to the server ! -------\n"


Server::Server(void): TcpConnection("8080"), nbConnectedClients(0) { }

Server::Server(const char *port): TcpConnection(port), nbConnectedClients(0) { }

Server::~Server(void) { }

void    Server::sendGreetingMsg(const Client &cl) const
{
    this->sendDataToFd(cl.getFd(), WELCOME_MSG);
}

void    Server::handleNewClient(void)
{
    Client cl;
    try 
    {
        this->acceptClientConnection(&cl);
    }
    catch(TcpAcceptException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    sendGreetingMsg(cl);
    std::cout << cl;
    this->clients.insert(std::pair<int, Client>(cl.getFd(), cl));
    this->nbConnectedClients++;
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
        this->receivedMessages.push_back(data);
        cl.setData(data);
    }
    std::cout << cl;
}

std::string  Server::getClientIp(struct sockaddr_storage remoteAddr)
{
    char    remoteIp[INET6_ADDRSTRLEN];
    inet_ntop(remoteAddr.ss_family, getInAddr((struct sockaddr*)&remoteAddr), remoteIp, INET6_ADDRSTRLEN);
    std::string ip(remoteIp);
    return (ip);
}

void    Server::acceptClientConnection(Client *cl)
{
    struct sockaddr_storage remoteAddr;
    int fd = this->acceptConnection(&remoteAddr);
    cl->setIp(this->getClientIp(remoteAddr));
    cl->setFd(fd);
    cl->setConnected(true);
    std::cout << "New connection ...\n";
}

bool    Server::isClientConnecting(int fd)
{
    return (fd == this->getListenerFd());
}

void    Server::runOnce(void)
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
            if (isClientConnecting(fd))
                this->handleNewClient();
            else
                this->handleClientData(fd);
        }
    }
}

void    Server::start(void)
{
    this->TcpConnection::init(TO_LISTEN);
    while (true)
    {
        this->runOnce();
    }
}
