#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

# include "../irc_client/irc_client.hpp"
# include "../server/server.hpp"
# include "../cmd_parser/cmd_parser.hpp"
# include <map>
# include <vector>
# include <iostream>

class IrcServer : public Server {
    private:
        std::map<std::string, IrcClient*> users;
        std::vector<std::string> commands;

    public:
        IrcServer(void);
        IrcServer(const char *port);
        ~IrcServer(void);

        void    start(void);
        
        void    nick(const t_nick &nick);
        void    privMsg(const t_privMsg &privMsg);
        void    user(const t_user &user);
        void    unknown(const t_unknown &unknown);
};

#endif
