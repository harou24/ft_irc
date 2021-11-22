#ifndef MOCK_SERVER_HPP
# define MOCK_SERVER_HPP

# include "../server/server.hpp"

class MockServer : public Server {
    public:
        MockServer(void);
        ~MockServer(void);

        void    runUntilMsgFromClientReceived(void);
};

#endif
