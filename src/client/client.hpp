#ifndef CLIENT_HPP
# define CLIENT_HPP

# define MAX_BUFF_SIZE 256

# include <sys/socket.h>
# include <netinet/in.h>

#include <iostream>

class Client {

   private:
        int                     fd;
        std::string             ip;
        std::string             dataBuffer;

    public:
        Client(void);
        Client(int fd, std::string ip);
        ~Client(void);
        
        int                     getFd(void) const;
        std::string             getDataBuffer(void) const;
        std::string             getIP(void) const;

        void                    setDataBuffer(std::string data);
};

std::ostream &operator << (std::ostream &output, const Client &cl);

#endif
