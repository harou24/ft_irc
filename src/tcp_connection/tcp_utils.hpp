#ifndef TCP_UTILS_HPP
# define TCP_UTILS_HPP

#include <netinet/in.h>
#include <sys/select.h>
#include <netdb.h>

#include <iostream>

void    *getInAddr(struct sockaddr *sa);
void    setSockAddrConfig(struct addrinfo *hints);
void    zeroFdSet(fd_set *set);
bool    isFdInSet(int fd, fd_set *set);
void    addFdToSet(int fd, fd_set *set);
void    removeFdFromSet(int fd, fd_set *set);
void    dieWithMsg(const char *msg);

struct addrinfo     *getAddrInfo(const char *hostname, const char *servname);
void                freeAddrInfo(struct addrinfo *addrinfo);

int     assignAddrToFd(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int     connectFdToAddr(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

std::string     getHostName(void);

#endif
