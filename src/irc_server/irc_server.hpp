#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

# include "../server/server.hpp"
# include "../irc_client/irc_client.hpp"
# include "../message/message.hpp"
# include "../channel/channel.hpp"

# include <map>
# include <vector>
# include <iostream>

class IrcServer {
    private:
        Server *server;
        std::map<std::string, IrcClient*> *users;
        std::map<std::string, Channel*> *channels;

    public:
        IrcServer(void);
        IrcServer(const char *port);
        ~IrcServer(void);

        void    start(void);
        void    updateUsersStatus(void);
        void    handleUnreadMessages(void);
        bool    userExists(const std::string &nickName) const;
        
        bool    channelExists(const std::string &name) const;
        void    handleLastReceivedMessage(std::vector<Message*>::iterator lastMsg);

        std::string     execCmd(std::vector<Message*>::iterator lastMsg);
        bool            isNickInUse(const std::string &nickName);

        void            addUser(const std::string &nickName, IrcClient *cl);
        void            addChannel(const std::string &name, Channel *channel);
        Channel*        getChannel(const std::string &name) const;
        IrcClient*      removeUser(const std::string &nickName);

        Server&   getServer(void) const;
        IrcClient*      getUserByFd(const int fd);

        std::map<std::string, IrcClient*>*  getUsers(void) const;
        std::map<std::string, Channel*>*  getChannels(void) const;
        std::vector<Message*>::iterator     getLastUnreadMsg(void);

        void    removeClientWithReply(const Client *cl, const std::string &reply);
};

#endif
