#include "tcp_connection.hpp"
#include "tcp_exceptions.hpp"
#include "tcp_utils.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>

#include <errno.h>
#include "../utils/colors.h"

#define MAX_PENDING_CONNECTION 10
#define MAX_BUFF_SIZE 256

struct timeval TIMEOUT = {2, 0};

TcpConnection::TcpConnection(void)
{
    this->port = "8080";
    zeroFdSet(&this->masterFds);
    zeroFdSet(&this->readFds);
    this->listenerFd = -1;
    this->connectingFd = -1;
    this->fdMax = 0;
}

TcpConnection::TcpConnection(const char *port) : port(port)
{
    zeroFdSet(&this->masterFds);
    zeroFdSet(&this->readFds);
    this->listenerFd = -1;
    this->connectingFd = -1;
    this->fdMax = 0;
}

TcpConnection::TcpConnection(const char *hostname, const char *port)
{
    this->hostname = hostname;
    this->port = port;
    this->port = "8080";
    zeroFdSet(&this->masterFds);
    zeroFdSet(&this->readFds);
    this->listenerFd = -1;
    this->connectingFd = -1;
    this->fdMax = 0;
}

TcpConnection::~TcpConnection(void) { }

int     TcpConnection::assignAddrToListenerFd(int sockFd, const struct sockaddr *addr, socklen_t addrlen)
{
    const bool  enableOpt = true;
    setsockopt(this->listenerFd, SOL_SOCKET, SO_REUSEADDR, (const void *)&enableOpt, sizeof(int));
    return(assignAddrToFd(sockFd, addr, addrlen));
}

int     TcpConnection::findFd(e_fdType type, struct addrinfo *addresses)
{
    t_ptrToFunction function = NULL;
    int             fd;
    
    if (type == TO_LISTEN)
        function = &assignAddrToFd;
    else if(type == TO_CONNECT)
        function = &connectFdToAddr;
    try
    {
        fd = this->applyFunctionToAddresses(function, addresses);
    }
    catch (TcpException &e)
    {
        std::cerr << e.what();
    }
    return(fd);
}

int    TcpConnection::applyFunctionToAddresses(t_ptrToFunction function, struct addrinfo *addresses)
{
    struct addrinfo     *tmpAddrInfo;
    int                 fd;

    for(tmpAddrInfo = addresses; tmpAddrInfo != NULL; tmpAddrInfo = tmpAddrInfo->ai_next)
    {
        fd = socket(tmpAddrInfo->ai_family, tmpAddrInfo->ai_socktype, tmpAddrInfo->ai_protocol);
        if (fd < 0)
            continue;
        if (function(fd, tmpAddrInfo->ai_addr, tmpAddrInfo->ai_addrlen) < 0)
        {
            close(fd);
            continue;
        }
        break;
    }
    freeAddrInfo(addresses);
    if (tmpAddrInfo == NULL)
    {
        close(this->connectingFd);
        close(this->listenerFd);
        throw TcpAssignAddrToFdException();
    }
    return (fd);
}

int            TcpConnection::getFd(e_fdType type, const char *hostname, const char *port)
{
    struct addrinfo *addrInfo;

    try
    {
        addrInfo = getAddrInfo(hostname, port);
    }
    catch(TcpGetAddrInfoException &e)
    {
        std::cerr << e.what();
    }
    int  fd = this->findFd(type, addrInfo);
    return (fd);
}

void    TcpConnection::init(e_fdType type)
{
    if (type == TO_LISTEN)
    {
        this->listenerFd = this->getFd(TO_LISTEN, NULL, this->port);
        if (listen(this->listenerFd, MAX_PENDING_CONNECTION) == -1)
            dieWithMsg("listen() error @_@\n");
        addFdToSet(this->listenerFd, &this->masterFds);
        this->setFdMax(this->listenerFd);
    }
    else if (type == TO_CONNECT)
    {
        this->connectingFd = this->getFd(TO_CONNECT, this->hostname, this->port);
        addFdToSet(this->connectingFd, &this->masterFds);
        addFdToSet(0, &this->masterFds);
        this->setFdMax(this->connectingFd);
    }
}

int    TcpConnection::acceptConnection(struct sockaddr_storage *remoteAddr)
{
    socklen_t               addrlen;
    int                     newfd;

    addrlen = sizeof(remoteAddr);
    newfd = accept(this->listenerFd, (struct sockaddr *)remoteAddr, &addrlen);

    if (newfd == -1)
        throw TcpAcceptException();
    else
    {
        addFdToSet(newfd, &this->masterFds);
        this->setFdMax(newfd);
    }
    return (newfd);
}

std::string TcpConnection::getDataFromFd(int fd)
{
    int nbytes;
    char buf[MAX_BUFF_SIZE];

    if ((nbytes = read(fd, buf, sizeof(buf))) <= 0)
    {
        if (nbytes == 0)
            std::cout << BG_RED << "TCP Connection lost ! " << RESET << "\n";
        else
        {
            std::cerr << "recv() error @_@\n";
            std::cerr << strerror(errno) << std::endl;
            return ("");
        }
    }
    buf[nbytes] = '\0';
    std::string data(buf);
    return (data);
}

bool        TcpConnection::sendDataToFd(const int fd, const std::string &data) const
{
    const char *dataToSend = data.c_str();
    return (write(fd, dataToSend, strlen(dataToSend)));
}

void    TcpConnection::updateFdsInSet(void)
{
    this->readFds = this->masterFds;
    if (select(this->fdMax + 1, &this->readFds, NULL, NULL, &TIMEOUT) == -1)
        throw TcpException();
}

fd_set  *TcpConnection::getReadFds(void) { return (&this->readFds); }

fd_set  *TcpConnection::getMasterFds(void) { return (&this->masterFds); }

int     TcpConnection::getListenerFd(void) const { return (this->listenerFd); }

int     TcpConnection::getFdMax(void) const { return (this->fdMax); }

void    TcpConnection::setFdMax(const int newMax) { this->fdMax = newMax; }

bool    TcpConnection::isFdReadyForCommunication(const int fd) { return (isFdInSet(fd, &this->readFds)); }

int     TcpConnection::getConnectingFd(void) const { return (this->connectingFd); }
