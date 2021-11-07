#include "client.hpp"
#include "../utils/colors.h"

#include <string.h>

#include<sstream>

Client::Client(void)
{
    this->fd = -1;
    this->connected = false;
}

Client::Client(int fd, std::string ip)
{
    this->fd = fd;
    this->ip = ip;
    this->connected = false;
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
    this->dataBuffer.assign(data);
}

bool            Client::isConnected(void) const
{
    return (this->connected);
}

void            Client::setConnected(bool status)
{
    this->connected = status;
}

void            Client::setIP(std::string newIP)
{
    this->ip = newIP;
}

void            Client::setFd(int newFd)
{
    this->fd = newFd;
}

std::ostream &operator << (std::ostream &output , const Client &cl)
{
	output << "Client {\n";
    if (cl.isConnected())
        output << "          STATUS:    " << GREEN << "connected" << RESET << std::endl;
    else
        output << "          STATUS:    " << RED << "disconnected" << RESET << std::endl;
    output << "          FD:        " << cl.getFd() << std::endl;
    output << "          IP:        " << cl.getIP() << std::endl;
    if (!cl.getDataBuffer().empty())
    {
        std::istringstream ss(cl.getDataBuffer());
        std::string del;
        output << "          DATA:      ";
        getline(ss, del, '\n');
        output << del << '\n';
        while(getline(ss, del, '\n'))
            output << "                     " << del << '\n';
    
    }    
    output << "}" << std::endl << std::endl;
	return (output);
}
