#ifndef CLIENT_HPP
# define CLIENT_HPP

# define MAX_BUFF_SIZE 256

# include <sys/socket.h>
# include <netinet/in.h>

class Client {

   private:
        int                     fd;
        struct sockaddr_storage remoteAddr;
        char                    remoteIP[INET6_ADDRSTRLEN];
        char                    dataBuffer[MAX_BUFF_SIZE];

    public:
        Client(void);
        Client(int fd, struct sockaddr_storage remoteAddr, char *remoteIp);
        ~Client(void);

};

#endif
