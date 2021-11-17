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
        IrcClient(std::string &nickName, std::string &userName, std::string &hostName, std::string &serverName);
        IrcClient(const IrcClient &cl);
        ~IrcClient(void);

		IrcClient& operator = (const IrcClient &cl);

        void            runCommunicationWithServer(void);
        void            connectToServer(void);

        void            setNickName(const std::string &nickName);
        std::string     getNickName(void) const;
        struct passwd    *getUserInfo(void);
};

#endif
