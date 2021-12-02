#ifndef IRC_CLIENT_HPP
# define IRC_CLIENT_HPP

# include "../client/client.hpp"

# include <iostream>

class IrcClient{
    private:
        Client *cl;
        std::string nickName;
        std::string userName;
        std::string hostName;
        std::string serverName;
        std::string realName;

    public:
        IrcClient(void);
        IrcClient(Client *cl, const std::string &nickName);
        ~IrcClient(void);

        void            setNickName(const std::string &nickName);
        void            setUserName(const std::string &userName);
        void            setHostName(const std::string &hostName);
        void            setServerName(const std::string &serverName);
        void            setRealName(const std::string &realName);

        std::string     getNickName(void) const;
        std::string     getUserName(void) const;
        std::string     getHostName(void) const;
        std::string     getServerName(void) const;
        std::string     getRealName(void) const;

        const   Client&     getClient(void) const;
        Client*             getClient(void);
        
        void    debug(void) const;
};

#endif
