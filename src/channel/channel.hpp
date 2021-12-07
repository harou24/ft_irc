#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <vector>

#include "../irc_client/irc_client.hpp"

class Channel {
    private:
            std::string name;
            IrcClient   *chop;
            std::vector<IrcClient*> *users;
            std::string topic;
            std::string mode;

    public:
            Channel(void);
            Channel(const std::string &name);
            Channel(const std::string &name, IrcClient *op);
            ~Channel(void);
            
            void    addUser(IrcClient *cl);

            void    setName(const std::string &name);
            void    setChop(IrcClient *cl);
            void    setTopic(const std::string &topic);
            void    setMode(const std::string &mode);

            std::string getName(void) const;
            IrcClient*  getChop(void) const;
            std::string getTopic(void) const;
            std::string getMode(void) const;

            std::string getChannelUsersAsString(void) const;

            void    debug(void) const;
};

#endif
