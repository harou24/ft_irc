#include "client.hpp"
#include <string.h>

Client::Client(void)
{
    this->fd = -1;
    memset(this->dataBuffer, 0, sizeof(char) * MAX_BUFF_SIZE);
    memset(this->remoteIP, 0, sizeof(char) * MAX_BUFF_SIZE);
}

Client::Client(int fd, struct sockaddr_storage remoteAddr)
{
    this->fd = fd;
    this->remoteAddr = remoteAddr;
    memset(this->dataBuffer, 0, sizeof(char) * MAX_BUFF_SIZE);
    memset(this->remoteIP, 0, sizeof(char) * MAX_BUFF_SIZE);
}

Client::~Client(void){ }
