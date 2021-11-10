#ifndef MOCK_CLIENT_HPP
# define MOCK_CLIENT_HPP

#include "../client/client.hpp"

class MockClient : public Client {
    private:

    public:
        MockClient(void);
        MockClient(const char *hostname, const char *port);
        ~MockClient(void);

        void        connectToServer(void);

};

#endif
