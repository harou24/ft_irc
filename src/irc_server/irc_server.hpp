#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

# include "../irc_client/irc_client.hpp"
# include "../server/server.hpp"
# include "../cmd_parser/cmd_parser.hpp"
# include "../message/message.hpp"

# include <map>
# include <vector>
# include <iostream>

class IrcServer {

    private:
        Server *server;
        std::map<std::string, IrcClient*> *users;

    public:
        IrcServer(void);
        IrcServer(const char *port);
        ~IrcServer(void);

        const Server& getServer(void) const;

        void    start(void);
        
        void    nick(const t_nick &nick);
        void    privMsg(const t_privMsg &privMsg);
        void    user(const t_user &user);
        void    unknown(const t_unknown &unknown);

        bool    userExists(const std::string &nickName) const;

        std::map<std::string, IrcClient*>*   getUsers(void) const;
        std::vector<Message*>::iterator     getLastUnreadMsg(void);
        IrcClient*  getUserByFd(const int fd);
        void        handleLastReceivedMessage(std::vector<Message*>::iterator lastMsg);
};

#endif
