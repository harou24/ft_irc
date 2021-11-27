#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

# include "../server/server.hpp"
# include "../irc_client/irc_client.hpp"
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

        std::string     execCmd(std::vector<Message*>::iterator lastMsg);
        
        std::string     nick(std::vector<Message*>::iterator lastMsg);
        std::string     userMode(std::vector<Message*>::iterator lastMsg);
        std::string     pong(std::vector<Message*>::iterator lastMsg);
        std::string     privMsg(std::vector<Message*>::iterator lastMsg);
        std::string     user(std::vector<Message*>::iterator lastMsg);
        std::string     whoIs(std::vector<Message*>::iterator lastMsg);
        std::string     unknown(std::vector<Message*>::iterator lastMsg);
        
        const Server&   getServer(void) const;
        IrcClient*      getUserByFd(const int fd);

        std::map<std::string, IrcClient*>*  getUsers(void) const;
        std::vector<Message*>::iterator     getLastUnreadMsg(void);
};

#endif
