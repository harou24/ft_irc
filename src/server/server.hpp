#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>

# include "../client/client.hpp"

# define MAX_CLIENTS 30
# define MAX_PENDING_CONNECTION 10

class Server {

    private:
        std::vector<Client> clients;
        fd_set              master;
        fd_set              readFds;
        int                 listener;
        int                 fdMax;
        const char          *port;

    public:
        Server(void);
        Server(const char *port);
        ~Server(void);
        
        void    init(void);
        void    run(void);
        void    handleNewClient(void);
        void    handleClientData(void);

};


#endif
