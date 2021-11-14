#ifndef IRC_SERVER_HPP
# define IRC_SERVER_HPP

# include "../user/user.hpp"

# include <map>
# include <iostream>

class IrcServer : public Server {
    private:
        std::map<std::string, User>
    public:
        void    start(void);
        void    runOnce(void);

        void    sendPrivMsg();

};

#endif
