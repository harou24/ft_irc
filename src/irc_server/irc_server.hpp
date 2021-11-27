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

        std::string     execCmd(const CmdParser &cmd);
        
        std::string     nick(const CmdParser &cmd);
        std::string     userMode(const CmdParser &cmd);
        std::string     pong(const CmdParser &cmd);
        std::string     privMsg(const CmdParser &cmd);
        std::string     user(const CmdParser &cmd);
        std::string     unknown(const CmdParser &cmd);
        
        const Server&   getServer(void) const;
        IrcClient*      getUserByFd(const int fd);

        std::map<std::string, IrcClient*>*  getUsers(void) const;
        std::vector<Message*>::iterator     getLastUnreadMsg(void);
};

#endif
