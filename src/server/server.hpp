#ifndef SERVER_HPP
# define SERVER_HPP

# include <map>
# include <stdexcept>

# include "../client/client.hpp"
# include "../tcp_connection/tcp_connection.hpp"

# define MAX_CLIENTS 30

class Server : public TcpConnection {

    private:
        std::map<int, Client>   clients;

    public:
        Server(void);
        Server(const char *port);
        ~Server(void);
        
        void    start(void);

        void    handleNewClient(void);
        void    handleClientData(int fd);
        void    handleClientRemoval(Client cl);
        void    sendGreetingMsg(const Client &cl);

        void    removeClient(Client cl);

        Client  getClient(int fd);
};


#endif
