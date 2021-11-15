#include "mock_client.hpp"
#include "../tcp_connection/tcp_utils.hpp"
#include "../utils/colors.h"

#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define CLIENT_MSG "-------------Hello World From Client-------------"

MockClient::MockClient(void) : Client(){ }
MockClient::MockClient(const char *hostname, const char *port) : Client(hostname, port) { }
MockClient::~MockClient(void) { }

void    MockClient::connectToServer(void)
{
    this->init(TO_CONNECT);
}

void    MockClient::runCommunicationWithServer(void)
{
    while (true)
    {
        std::string data = receiveMsg(this->getServerFd());
        if (!data.empty())
            std::cout << data << std::endl;
        std::cout << GREEN << "User:> " << RESET;
        for (std::string line; std::getline(std::cin, line);)
        {
            if (line == "/quit")
            {
                close(this->getServerFd());
                exit(EXIT_SUCCESS);
            }
            std::cout << line << std::endl;
            this->sendMsg(this->getServerFd(), line);
            std::cout << GREEN << "User:> " << RESET;
        }
    }
    close(this->getServerFd());
}
