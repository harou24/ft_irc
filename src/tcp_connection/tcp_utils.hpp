#ifndef TCP_UTILS_HPP
# define TCP_UTILS_HPP

#include <netinet/in.h>
#include <sys/select.h>
#include <netdb.h>

void    *getInAddr(struct sockaddr *sa);
void    setSockAddrConfig(struct addrinfo *hints);
void    zeroFdSet(fd_set *set);
bool    isFdInSet(int fd, fd_set *set);
void    addFdToSet(int fd, fd_set *set);
void    removeFdFromSet(int fd, fd_set *set);
void    dieWithMsg(const char *msg);

int     getAddrInfo(const char *hostname,
                        const char *servname,
                            const struct addrinfo *hints, 
                                    struct addrinfo **res);
#endif
