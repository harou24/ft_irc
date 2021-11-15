#ifndef MOCK_SERVER_HPP
# define MOCK_SERVER_HPP

class MockServer {
    public:
        MockServer(void);
        ~MockServer(void);

        void    runUntilMsgFromClientReceived(void);

};

#endif
