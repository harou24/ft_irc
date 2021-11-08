#include "client.hpp"
#include "../utils/colors.h"

#include <string.h>

#include<sstream>

Client::Client(void)
{
    this->fd = -1;
    this->connected = false;
}

Client::Client(const int fd, const std::string &ip)
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

std::string    Client::getIp(void) const
{
    return (this->ip);
}

std::string    Client::getData(void) const
{
    return (this->data);
}

void            Client::setData(const std::string &data)
{
    this->data.assign(data);
}

bool            Client::isConnected(void) const
{
    return (this->connected);
}

void            Client::setConnected(const bool status)
{
    this->connected = status;
}

void            Client::setIp(const std::string &newIp)
{
    this->ip = newIp;
}

void            Client::setFd(const int newFd)
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
    output << "          IP:        " << cl.getIp() << std::endl;
    if (!cl.getData().empty())
    {
        std::istringstream ss(cl.getData());
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
