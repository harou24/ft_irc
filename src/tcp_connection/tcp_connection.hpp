#ifndef TCP_CONNECTION_HPP
# define TCP_CONNECTION_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>

class TcpConnection {
    private:
        const char  *hostname;
        const char  *port;
        fd_set      masterFds;
        fd_set      readFds;
        int         listenerFd;
        int         connectingFd;
        int         fdMax;

    public:
        enum e_fdType
        {
            TO_CONNECT,
            TO_LISTEN 
        };
        
        TcpConnection(void);
        TcpConnection(const char *port);
        TcpConnection(const char *hostname, const char *port);
        virtual ~TcpConnection(void);

        void            init(e_fdType type);
        
        int             acceptConnection(struct sockaddr_storage *remoteAddr);
        bool            isFdReadyForCommunication(const int fd);
        int             assignAddrToListenerFd(int sockFd, const struct sockaddr *addr, socklen_t addrlen);

        std::string     getDataFromFd(int fd);
        bool            sendDataToFd(const int fd, const std::string &data) const;
        
        void            updateFdsInSet(void);
        int             findFd(e_fdType type, struct addrinfo *addresses);

        typedef         int (*t_ptrToFunction)(int, const struct sockaddr*, socklen_t);
        int             applyFunctionToAddresses(t_ptrToFunction function, struct addrinfo *addresses);
        
        fd_set          *getMasterFds(void);
        fd_set          *getReadFds(void);
        int             getListenerFd(void) const;
        int             getFdMax(void) const;
        int             getFd(e_fdType type, const char *hostname, const char *port);
        int             getConnectingFd(void) const;

        void            setFdMax(const int newMax);


};

#endif
