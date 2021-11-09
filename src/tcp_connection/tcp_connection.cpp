#include "tcp_connection.hpp"
#include "tcp_utils.hpp"
#include "tcp_exceptions.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define MAX_PENDING_CONNECTION 10
#define MAX_BUFF_SIZE 256

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

int     TcpConnection::assignAddrToListenerFd(int sockFd, const struct sockaddr *addr, socklen_t addrlen)
{
    const bool  enableOpt = true;
    setsockopt(this->listenerFd, SOL_SOCKET, SO_REUSEADDR, (const void *)&enableOpt, sizeof(int));
    return(assignAddrToFd(sockFd, addr, addrlen));
}

int     TcpConnection::findFd(e_fdType type, struct addrinfo *addresses)
{
    t_ptrToFunction function = NULL;
    
    if (type == TO_LISTEN)
        function = &assignAddrToFd;
    else if(type == TO_CONNECT)
        function = &connectFdToAddr;
    return(this->applyFunctionToAddresses(function, addresses));
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
    if (tmpAddrInfo == NULL)
        throw TcpAssignAddrToFdException();
    return (fd);
}

void    TcpConnection::init(void)
{
    struct addrinfo     hints;
    struct addrinfo     *addrInfo;
    int                 ret;

    setSockAddrConfig(&hints);
    if ((ret = getAddrInfo(NULL, this->port, &hints, &addrInfo)) != 0)
        throw TcpGetAddrInfoException(gai_strerror(ret));
    this->listenerFd = this->findFd(TO_LISTEN, addrInfo);
    freeaddrinfo(addrInfo);
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
        throw TcpAcceptException();
    else
    {
        addFdToSet(newfd, &this->masterFds);
        this->setFdMax(newfd);
        inet_ntop(remoteaddr.ss_family, getInAddr((struct sockaddr*)&remoteaddr), remoteIP, INET6_ADDRSTRLEN);
        std::cout << "New connection ..." << std::endl;

        std::string ip(remoteIP);
        cl.setIp(ip);
        cl.setFd(newfd);
        cl.setConnected(true);
    }
}

std::string TcpConnection::getDataFromFd(int fd)
{
    int nbytes;
    char buf[MAX_BUFF_SIZE];

    if ((nbytes = recv(fd, buf, sizeof(buf), 0)) <= 0)
    {
        if (nbytes == 0)
            std::cout << "TCP Connection lost !\n";
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

void  TcpConnection::setFdMax(const int newMax)
{
    this->fdMax = newMax;
}

bool    TcpConnection::isFdReadyForCommunication(const int fd)
{
    return (isFdInSet(fd, &this->readFds));
}

