#include "server.hpp"
#include "ostream_server.hpp"
#include "../client/ostream_client.hpp"
#include "../tcp_connection/tcp_utils.hpp"
#include "../tcp_connection/tcp_exceptions.hpp"
#include "../parser/parser.hpp"

#include <unistd.h>
#include <arpa/inet.h>

#include <ctime>
#include <time.h>

#include "errno.h"

#define WELCOME_MSG "------- Welcome to the server ! -------\n"


Server::Server(void) :
    TcpConnection("8080"),
            nbConnectedClients(0), 
                clients(new std::map<int, Client*>()),
                    messages(new std::vector<Message*>())
{ }

Server::Server(const char *port) :
    TcpConnection(port),
            nbConnectedClients(0),
                clients(new std::map<int, Client*>()),
                    messages(new std::vector<Message*>())
{ }

Server::~Server(void) { }

void    Server::sendGreetingMsg(const Client *cl) const
{
    this->sendDataToFd(cl->getFd(), WELCOME_MSG);
}

void    Server::sendMsg(const int fd, const std::string &msg) const
{
    this->sendDataToFd(fd, msg);
}

void    Server::handleNewClient(void)
{
    Client *cl = new Client();
    try 
    {
        this->acceptClientConnection(cl);
    }
    catch(TcpAcceptException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    sendGreetingMsg(cl);
    this->clients->insert(std::pair<int, Client*>(cl->getFd(), cl));
    this->nbConnectedClients++;
}

Client*    Server::getClient(const int fd)
{
    std::map<int, Client*>::iterator it;
    it = this->clients->find(fd);
    return(it->second);
}

void    Server::removeClient(const Client *cl)
{
        std::map<int, Client*>::iterator it;
        it = this->clients->find(cl->getFd());
        this->clients->erase(it);
}

void    Server::handleClientRemoval(const Client *cl)
{
        close(cl->getFd());
        removeFdFromSet(cl->getFd(), this->getMasterFds());
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

    Client *cl = this->getClient(fd);
    if (!cl || data.empty())
    {
        cl->setConnected(false);
        this->nbConnectedClients--;
        this->handleClientRemoval(cl);
    }
    else
    {
        if (data.find("\n") != std::string::npos)
        {
            Parser p;
            std::vector<std::string> msgs = p.split(data, '\n');
            for (std::vector<std::string>::iterator cmd = msgs.begin(); cmd != msgs.end(); cmd++)
            {
                this->messages->push_back(new Message(*cmd));
            }
        }
        else
            this->messages->push_back(new Message(data));
        cl->setData(data);
    }
}

std::string  Server::getClientIp(struct sockaddr_storage *remoteAddr)
{
    char    remoteIp[INET6_ADDRSTRLEN];
    const char *ipp = inet_ntop(remoteAddr->ss_family, getInAddr((struct sockaddr*)remoteAddr), remoteIp, INET6_ADDRSTRLEN);
    if (!ipp)
        strerror(errno);
    std::string ip(ipp);
    return (ip);
}

void    Server::acceptClientConnection(Client *cl)
{
    struct sockaddr_storage remoteAddr;
    int fd = this->acceptConnection(&remoteAddr);
    std::string ip = this->getClientIp(&remoteAddr);
    cl->setIp(ip);
    cl->setFd(fd);
    cl->setConnected(true);
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

std::map<int, Client*>*   Server::getClients(void) const
{
    return (this->clients);
}

std::vector<Message*>*   Server::getMessages(void) const
{
    return (this->messages);
}

int                      Server::getNbConnectedClients(void) const
{ 
    return (this->nbConnectedClients);
}

std::string             Server::getLocalTime(void) const
{
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    std::string localTime(asctime(timeinfo));
    Parser p;
    std::vector<std::string> hour = p.split(localTime);
    return (hour[3]);
}

void    Server::removeMsg(std::vector<Message*>::iterator toRemove)
{
    Message *msg = *toRemove;
    this->messages->erase(toRemove);
    delete(msg);
}
