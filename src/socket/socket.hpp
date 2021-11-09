#ifndef SOCKET_HPP
# ifdef SOCKET_HPP

# include <iostream>

class Socket {
    private:
        int         fd;
        std::string data;

    public:
        Socket(void);
        Socket(int fd);
        ~Socket(void);

        void    send(std::string data);
        void    receive(void);
        
        void    setFd(const int fd);
        int     getFd(void) const;

        void            sentData(const std::string data);
        std::string     getData(void) const;
};

#endif
