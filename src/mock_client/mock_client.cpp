#include "mock_client.hpp"
#include "../tcp_connection/tcp_utils.hpp"
#include <iostream>
#include <unistd.h>

#define CLIENT_MSG "-------------Hello World From Client-------------"

MockClient::MockClient(void) : Client(){ }
MockClient::MockClient(const char *hostname, const char *port) : Client(hostname, port) { }
MockClient::~MockClient(void) { }

void    MockClient::connectToServer(void)
{
    this->init(TO_CONNECT);
    std::string data = receiveMsg(this->getServerFd());
    std::cout << "Data from server->" << data << std::endl;
    std::string helloFromClient(CLIENT_MSG);
    this->sendMsg(this->getServerFd(), helloFromClient);
    close(this->getServerFd());
}
