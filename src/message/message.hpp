#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "../client/client.hpp"

# include <iostream>

class Message {
    private:
        Client*         sentBy;
        std::string     time;
        std::string     data;
        bool            hasBeenRead;

    public:
        Message(void);
        Message(const std::string &msg);
        Message(Client *cl, const std::string &time, const std::string &msg);
        Message(const Message &m);
        ~Message(void);

        Client*         getSender(void);
        std::string     getTime(void) const;
        std::string     getData(void) const;
        bool            hasItBeenRead(void) const;

        void    setData(const std::string &data);
        void    setRead(const bool status);
};

#endif
