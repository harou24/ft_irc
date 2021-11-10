#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sys/socket.h>
# include <netinet/in.h>

# include <iostream>


# include "../tcp_connection/tcp_connection.hpp"

class Client : public TcpConnection {

   private:
        bool                    connected;
        int                     fd;
        std::string             ip;
        std::string             data;

    public:
        Client(void);
        Client(const int fd, const std::string &ip);
        ~Client(void);
        
        void                    sendMsg(const int fd, std::string &msg);
        std::string             receiveMsg(const int fd);

        int                     getServerFd(const char *hostname, const char *port);
        
        int                     getFd(void) const;
        std::string             getData(void) const;
        std::string             getIp(void) const;
        bool                    isConnected(void) const;

        void                    setIp(const std::string &newIp);
        void                    setFd(const int newFd);
        void                    setData(const std::string &data);
        void                    setConnected(const bool status);

};

#endif
