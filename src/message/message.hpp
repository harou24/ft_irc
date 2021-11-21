#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>

class Message {
    private:
        std::string data;
        bool        hasBeenRead;

    public:
        Message(void);
        Message(const std::string &msg);
        Message(const Message &m);
        ~Message(void);

        std::string getData(void) const;
        bool        hasItBeenRead(void) const;

        void    setData(const std::string &data);
        void    setRead(const bool status);
};


#endif
