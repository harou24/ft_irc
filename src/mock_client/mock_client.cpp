#include "mock_client.hpp"
#include "../tcp_connection/tcp_utils.hpp"
#include <iostream>
#include <unistd.h>

MockClient::MockClient(void) : Client(){ }
MockClient::~MockClient(void) { }

void    MockClient::connectToServer(const char *hostname, const char *port)
{
    struct addrinfo hints;
    struct addrinfo *servInfo;

    setSockAddrConfig(&hints);
    if (getAddrInfo(hostname, port, &hints, &servInfo) != 0)
    {
        dieWithMsg("Error : getAddrInfo...\n");
    }
    int servFd = this->findFd(TO_CONNECT, servInfo);
    freeaddrinfo(servInfo);
    std::string data = getDataFromFd(servFd);
    std::cout << "Data from server->" << data << std::endl;
    this->sendData(servFd, "Hello World From Client");
    close(servFd);
}
