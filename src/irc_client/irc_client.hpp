#ifndef IRC_CLIENT_HPP
# define IRC_CLIENT_HPP

# include "../client/client.hpp"

# include <iostream>

class IrcClient : public Client {
    private:
        std::string nickName;
        std::string userName;
        std::string hostName;
        std::string serverName;
        std::string realName;

    public:
        IrcClient(void);
        IrcClient(const std::string &nickName);
        IrcClient(const char *hostName, const char *port);
        IrcClient(const std::string &nickName,
                    const std::string &userName,
                        const std::string &hostName,
                            const std::string &serverName,
                                const std::string &realName);
        IrcClient(const IrcClient &cl);
        IrcClient(const Client &cl);
        ~IrcClient(void);

		IrcClient& operator = (const IrcClient &cl);
        void            runCommunicationWithServer(void);
        void            connectToServer(void);

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
        
        struct passwd    *getUserInfo(void);

        void    debug(void) const;
        std::string* getReceivedMsg(void);
};

#endif
