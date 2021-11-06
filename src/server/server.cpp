#include "server.hpp"
#include "server_utils.hpp"

#include <unistd.h>
#include <arpa/inet.h>

Server::Server(void)
{
    this->port = "8080";
    zeroFdSet(&this->master);
    zeroFdSet(&this->readFds);
    this->listener = -1;
    this->fdMax = 0;
}

Server::Server(const char *port): port(port)
{
    this->port = port;
    zeroFdSet(&this->master);
    zeroFdSet(&this->readFds);
    this->listener = -1;
    this->fdMax = 0;
}

void    Server::initTcpConnection(void)
{
    struct addrinfo hints;
    struct addrinfo *ai;
    struct addrinfo *p;
    int             rv;
    int             yes = 1;

    setSockAddrConfig(&hints);
    if ((rv = getaddrinfo(NULL, this->port, &hints, &ai)) != 0)
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(EXIT_FAILURE);
    }
    for(p = ai; p != NULL; p = p->ai_next)
    {
        this->listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (this->listener < 0)
            continue;
        setsockopt(this->listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (bind(this->listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(this->listener);
            continue;
        }
        break;
    }
    freeaddrinfo(ai);
    if (p == NULL)
        dieWithMsg("bind() error @_@\n");
    if (listen(this->listener, MAX_PENDING_CONNECTION) == -1)
        dieWithMsg("listen() error @_@\n");
}

void    Server::setFdMax(int newFd)
{
    if (newFd > this->fdMax)
        this->fdMax = newFd;
}

void    Server::handleNewClient(void)
{
    socklen_t               addrlen;
    int                     newfd;
    struct sockaddr_storage remoteaddr;
    char                    remoteIP[INET6_ADDRSTRLEN];

    addrlen = sizeof(remoteaddr);
    newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);

    if (newfd == -1)
        dieWithMsg("accept() error @_@\n");
    else
    {
        addFdToSet(newfd, &this->master);
        this->setFdMax(newfd);
        inet_ntop(remoteaddr.ss_family, getInAddr((struct sockaddr*)&remoteaddr), remoteIP, INET6_ADDRSTRLEN);
        std::string ip(remoteIP);
        Client cl(newfd, ip);
        this->clients.insert(std::pair<int, Client>(newfd, cl));
    }
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
        removeFdFromSet(cl.getFd(), &this->master);
        this->removeClient(cl);
}

void    Server::handleClientData(Client cl)
{
    int nbytes;
    char buf[256];

    if ((nbytes = recv(cl.getFd(), buf, sizeof buf, 0)) <= 0)
    {
        if (nbytes == 0)
            std::cout << cl << std::endl << "DISCONNECTED\n";
        else
            std::cerr << "recv() error @_@\n";
    }
    else
    {
        std::string data(buf);
        cl.setDataBuffer(data);
        printf("DATA from Client->%s\n", buf);
    }
}

void    Server::start(void)
{
    
}
