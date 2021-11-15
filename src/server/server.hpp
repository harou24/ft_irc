#ifndef SERVER_HPP
# define SERVER_HPP

# include <map>
# include <vector>
# include <stdexcept>

# include "../client/client.hpp"
# include "../tcp_connection/tcp_connection.hpp"

# define MAX_CLIENTS 30

class Server : public TcpConnection {

    private:
        std::map<int, Client*>   clients;
        int                     nbConnectedClients;

    public:
        std::vector<std::string> receivedMessages;
        Server(void);
        Server(const char *port);
        ~Server(void);
       
        void    runOnce(void);
        void    start(void);

        void    handleNewClient(void);
        void    handleClientData(const int fd);
        void    handleClientRemoval(const Client *cl);
        void    sendGreetingMsg(const Client *cl) const;

        void    removeClient(const Client *cl);
        void    acceptClientConnection(Client *cl);
        Client  *getClient(const int fd);
        std::string  getClientIp(struct sockaddr_storage remoteAddr);
        
        std::map<int, Client*>   getClients(void) const;
        int                     getNbConnectedClients(void) const;

        bool        isClientConnecting(int fd);

        void        setNbConnectedClients(const int nbConnected);

};


#endif
