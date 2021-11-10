#ifndef MOCK_CLIENT_HPP
# define MOCK_CLIENT_HPP

#include "../client/client.hpp"

class MockClient : public Client {
    private:

    public:
        MockClient(void);
        ~MockClient(void);

        void        connectToServer(const char *hostname, const char *port);

};

#endif
