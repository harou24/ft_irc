#include "client.hpp"
#include <string.h>

Client::Client(void)
{
    this->fd = -1;
}

Client::Client(int fd, std::string ip)
{
    this->fd = fd;
    this->ip = ip;
}

Client::~Client(void){ }

int     Client::getFd(void) const
{
    return (this->fd);
}

std::string    Client::getIP(void) const
{
    return (this->ip);
}

std::string    Client::getDataBuffer(void) const
{
    return (this->dataBuffer);
}

void            Client::setDataBuffer(std::string data)
{
    this->dataBuffer = data;
}

std::ostream &operator<<(std::ostream &output , const Client &cl)
{
	output << "Client {\n";
    output << "          FD:   " << cl.getFd() << std::endl;
    output << "          IP:   " << cl.getIP() << std::endl;
    output << "          DATA: " << cl.getDataBuffer() << "\n}" << std::endl;
	return (output);
}
