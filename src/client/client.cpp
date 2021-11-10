#include "client.hpp"
#include "../tcp_connection/tcp_utils.hpp"
#include "../tcp_connection/tcp_exceptions.hpp"

#include <string.h>

Client::Client(void) : connected(false), fd(-1)  { }

Client::Client(const int fd, const std::string &ip) : connected(false), fd(fd), ip(ip) { }

Client::~Client(void){ }


void            Client::sendMsg(const int fd, std::string &msg) { this->sendDataToFd(fd, msg); }

std::string     Client::receiveMsg(const int fd) { return (this->getDataFromFd(fd)); }

int            Client::getServerFd(const char *hostname, const char *port)
{
    return (this->TcpConnection::getFd(TO_CONNECT, hostname, port));
}

int             Client::getFd(void) const { return (this->fd); }

std::string     Client::getIp(void) const { return (this->ip); }

std::string     Client::getData(void) const { return (this->data); }

bool            Client::isConnected(void) const { return (this->connected); }


void            Client::setData(const std::string &data) { this->data.assign(data); }

void            Client::setConnected(const bool status) { this->connected = status; }

void            Client::setIp(const std::string &newIp) { this->ip = newIp; }

void            Client::setFd(const int newFd) { this->fd = newFd; }

