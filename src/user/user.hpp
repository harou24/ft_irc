#ifndef USER_HPP
# define USER_HPP


# include <iostream>

class User {
    private:
        std::string nickName;
        std::string userName;
        std::string hostName;
        std::string serverName;
        std::string realName;

    public:
        User(void);
        User(const std::string &nickName);
        User(const char *hostName, const char *port);
        User(std::string &nickName, std::string &userName, std::string &hostName, std::string &serverName);
        ~User(void);

        void            setNickName(const std::string &nickName);
        std::string     getNickName(void) const;

};

#endif
