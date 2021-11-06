#ifndef SERVER_HPP
# define SERVER_HPP

# include <map>

# include "../client/client.hpp"

# define MAX_CLIENTS 30
# define MAX_PENDING_CONNECTION 10

class Server {

    private:
        std::map<int, Client>   clients;
        fd_set                  master;
        fd_set                  readFds;
        int                     listener;
        int                     fdMax;
        const char              *port;

    public:
        Server(void);
        Server(const char *port);
        ~Server(void);
        
        void    initTcpConnection(void);
        void    start(void);

        void    handleNewClient(void);
        void    handleClientData(int fd);
        void    handleClientRemoval(Client cl);

        void    removeClient(Client cl);

        void    setFdMax(int newFdMax);

        Client  getClient(int fd);
};


#endif
