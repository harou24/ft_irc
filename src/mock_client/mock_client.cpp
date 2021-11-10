#include "mock_client.hpp"
#include "../tcp_connection/tcp_utils.hpp"
#include <iostream>
#include <unistd.h>

#define CLIENT_MSG "-------------Hello World From Client-------------"

MockClient::MockClient(void) : Client(){ }
MockClient::~MockClient(void) { }

void    MockClient::connectToServer(const char *hostname, const char *port)
{
    int servFd = this->getServerFd(hostname, port);
    std::string data = receiveMsg(servFd);
    std::cout << "Data from server->" << data << std::endl;
    std::string helloFromClient(CLIENT_MSG);
    this->sendMsg(servFd, helloFromClient);
    close(servFd);
}
