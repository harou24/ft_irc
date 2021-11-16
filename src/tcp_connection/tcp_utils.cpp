#include "tcp_utils.hpp"
#include "tcp_exceptions.hpp"

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <iostream>

void    *getInAddr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

struct addrinfo     *getAddrInfo(const char *hostname, const char *servname)
{
    struct addrinfo hints;
    struct addrinfo *addrinfo;
    int             ret;

    setSockAddrConfig(&hints);
    if ((ret = getaddrinfo(hostname, servname, &hints, &addrinfo)) != 0)
            throw TcpGetAddrInfoException(gai_strerror(ret));
    return (addrinfo);
}

void                freeAddrInfo(struct addrinfo *addrinfo)
{
    freeaddrinfo(addrinfo);
}

void    setSockAddrConfig(struct addrinfo *hints)
{
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
}

void    zeroFdSet(fd_set *set)
{
    FD_ZERO(set);
}

bool    isFdInSet(int fd, fd_set *set)
{
    return (FD_ISSET(fd, set));
}

void    addFdToSet(int fd, fd_set *set)
{
    FD_SET(fd, set);
}

void    removeFdFromSet(int fd, fd_set *set)
{
    FD_CLR(fd, set);
}

void    dieWithMsg(const char *msg)
{
    std::cout << msg << std::endl;
    exit(EXIT_FAILURE);
}

int     assignAddrToFd(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int     ret = bind(sockfd, addr, addrlen);
    if (ret == -1)
        std::cout << "bind() error, value of errno is " << errno << "\nError : " << strerror(errno) << "\n";
    return(ret);
}

int     connectFdToAddr(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    return (connect(sockfd, addr, addrlen));
}
