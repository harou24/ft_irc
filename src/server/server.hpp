#ifndef SERVER_HPP
# define SERVER_HPP

# include "../client/client.hpp"
# include "../tcp_connection/tcp_connection.hpp"
# include "../message/message.hpp"

# include <map>
# include <vector>
# include <stdexcept>

# define MAX_CLIENTS 30

class Server : public TcpConnection {

    private:
        int nbConnectedClients;
        std::map<int, Client*> *clients;
        std::vector<Message*> *messages;

    public:
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

        void            setNbConnectedClients(const int nbConnected);

        bool            isClientConnecting(int fd);
        int             getNbConnectedClients(void) const;
        Client          *getClient(const int fd);
        std::string     getClientIp(struct sockaddr_storage *remoteAddr);
        std::string     getLocalTime(void) const;

        std::map<int, Client*>* getClients(void) const;
        std::vector<Message*>*  getMessages(void) const;

        void    removeMsg(std::vector<Message*>::iterator toRemove);

};

#endif
