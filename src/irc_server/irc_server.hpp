#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

# include "../irc_client/irc_client.hpp"
# include "../server/server.hpp"

# include <map>
# include <vector>
# include <iostream>

class IrcServer : public Server {
    private:
        std::map<std::string, IrcClient> users;
        std::vector<std::string> commands;

    public:
        IrcServer(void);
        IrcServer(const char *port);
        ~IrcServer(void);

        void    start(void);
        void    sendPrivMsg();

};

#endif
