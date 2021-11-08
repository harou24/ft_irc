#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sys/socket.h>
# include <netinet/in.h>

#include <iostream>

class Client {

   private:
        bool                    connected;
        int                     fd;
        std::string             ip;
        std::string             data;

    public:
        Client(void);
        Client(const int fd, const std::string &ip);
        ~Client(void);
        
        int                     getFd(void) const;
        std::string             getData(void) const;
        std::string             getIp(void) const;
        bool                    isConnected(void) const;

        void                    setIp(const std::string &newIp);
        void                    setFd(const int newFd);
        void                    setData(const std::string &data);
        void                    setConnected(const bool status);
};

std::ostream &operator << (std::ostream &output, const Client &cl);

#endif
