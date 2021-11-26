#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

# include "../server/server.hpp"
# include "../irc_client/irc_client.hpp"
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

        void    start(void);
        void    updateUsersStatus(void);
        void    handleUnreadMessages(void);
        bool    userExists(const std::string &nickName) const;
        void    handleLastReceivedMessage(std::vector<Message*>::iterator lastMsg);
        
        std::string     nick(const t_nick &nick);
        std::string     userMode(const t_userMode &mode);
        std::string     pong(const t_ping &ping);
        void            privMsg(const t_privMsg &privMsg);
        void            user(const t_user &user);
        void            unknown(const t_unknown &unknown);
        
        const Server&   getServer(void) const;
        IrcClient*      getUserByFd(const int fd);

        std::map<std::string, IrcClient*>*  getUsers(void) const;
        std::vector<Message*>::iterator     getLastUnreadMsg(void);
};

#endif
