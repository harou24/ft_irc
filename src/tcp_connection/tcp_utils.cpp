#include "tcp_utils.hpp"

#include <string.h>
#include <stdlib.h>

#include <iostream>

void    *getInAddr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int     getAddrInfo(const char *hostname,
                        const char *servname,
                            const struct addrinfo *hints,
                                    struct addrinfo **res)
{
    return (getaddrinfo(hostname, servname, hints, res));
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
