#include "tcp_connection.hpp"
#include "../server/server_utils.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define MAX_PENDING_CONNECTION 10

TcpConnection::TcpConnection(void)
{
    this->port = "8080";
    zeroFdSet(&this->masterFds);
    zeroFdSet(&this->readFds);
    this->listenerFd = -1;
    this->fdMax = 0;
}

TcpConnection::TcpConnection(const char *port) : port(port)
{
    zeroFdSet(&this->masterFds);
    zeroFdSet(&this->readFds);
    this->listenerFd = -1;
    this->fdMax = 0;
}

TcpConnection::~TcpConnection(void) { }

void    TcpConnection::init(void)
{
    struct addrinfo hints;
    struct addrinfo *ai;
    struct addrinfo *p;
    int             rv;
    int             yes = 1;

    setSockAddrConfig(&hints);
    if ((rv = getaddrinfo(NULL, this->port, &hints, &ai)) != 0)
    {
    	std::cout << "getaddrinfo() failed !\n" << gai_strerror(rv) << std::endl;
        exit(EXIT_FAILURE);
    }
    for(p = ai; p != NULL; p = p->ai_next)
    {
        this->listenerFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (this->listenerFd < 0)
            continue;
        setsockopt(this->listenerFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (bind(this->listenerFd, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(this->listenerFd);
            continue;
        }
        break;
    }
    freeaddrinfo(ai);
    if (p == NULL)
        dieWithMsg("bind() error @_@\n");
    if (listen(this->listenerFd, MAX_PENDING_CONNECTION) == -1)
        dieWithMsg("listen() error @_@\n");
    addFdToSet(this->listenerFd, &this->masterFds);
    this->setFdMax(this->listenerFd);
}

void    TcpConnection::acceptClientConnection(Client &cl)
{
    socklen_t               addrlen;
    int                     newfd;
    struct sockaddr_storage remoteaddr;
    char                    remoteIP[INET6_ADDRSTRLEN];

    addrlen = sizeof(remoteaddr);
    newfd = accept(this->listenerFd, (struct sockaddr *)&remoteaddr, &addrlen);

    if (newfd == -1)
        dieWithMsg("accept() error @_@\n");
    else
    {
        addFdToSet(newfd, &this->masterFds);
        this->setFdMax(newfd);
        inet_ntop(remoteaddr.ss_family, getInAddr((struct sockaddr*)&remoteaddr), remoteIP, INET6_ADDRSTRLEN);
        std::cout << "New connection ..." << std::endl;

        std::string ip(remoteIP);
        cl.setIP(ip);
        cl.setFd(newfd);
        cl.setConnected(true);
    }
}

std::string TcpConnection::getDataFromFd(int fd)
{
    int nbytes;
    char buf[256];

    if ((nbytes = recv(fd, buf, sizeof buf, 0)) <= 0)
    {
        if (nbytes == 0)
        {
            std::cout << "TCP Connection lost !\n";
        }
        else
            std::cerr << "recv() error @_@\n";
    }
    buf[nbytes] = '\0';
    std::string data(buf);
    return (data);
}

void    TcpConnection::updateFdsInSet(void)
{
    this->readFds = this->masterFds;
    if (select(this->fdMax + 1, &this->readFds, NULL, NULL, NULL) == -1)
        dieWithMsg("select() error @_@\n");
}

fd_set  *TcpConnection::getReadFds()
{
    return (&this->readFds);
}

fd_set  *TcpConnection::getMasterFds()
{
    return (&this->masterFds);
}

int  TcpConnection::getListenerFd() const
{
    return (this->listenerFd);
}

int  TcpConnection::getFdMax() const
{
    return (this->fdMax);
}

void  TcpConnection::setFdMax(int newMax)
{
    this->fdMax = newMax;
}

bool    TcpConnection::isFdReadyForCommunication(int fd)
{
    return (isFdInSet(fd, &this->readFds));
}

TcpConnection::TcpAcceptException::TcpAcceptException(void){}
TcpConnection::TcpAcceptException::TcpAcceptException(const TcpAcceptException &cpy){*this = cpy;}
TcpConnection::TcpAcceptException::~TcpAcceptException(void) throw(){}

TcpConnection::TcpAcceptException& TcpConnection::TcpAcceptException::operator = (const TcpAcceptException&){return (*this);}
const char* TcpConnection::TcpAcceptException::what() const throw() {return ("Error : accept() function failed !");}
