#include "client.hpp"
#include "../tcp_connection/tcp_utils.hpp"
#include "../tcp_connection/tcp_connection.hpp"

#include <string.h>

Client::Client(void) : connected(false), fd(-1)  { }

Client::Client(const char *hostname, const char *port) : TcpConnection(hostname, port) { }

Client::Client(const int fd) : connected(false), fd(fd) { }

Client::Client(const Client &cl) : TcpConnection() 
{
    this->connected = cl.connected;
    this->fd = cl.fd;
    this->ip = cl.ip;
    this->data = cl.data;
}

Client::~Client(void){ }

Client& Client::operator = (const Client &cl)
{
    this->connected = cl.connected;
    this->fd = cl.fd;
    this->ip = cl.ip;
    this->data = cl.data;
    return (*this);
}

void            Client::sendMsg(const int fd, std::string &msg) { this->sendDataToFd(fd, msg); }

std::string     Client::receiveMsg(const int fd) { return (this->getDataFromFd(fd)); }

int            Client::getServerFd(const char *hostname, const char *port)
{
    return (this->TcpConnection::getFd(TO_CONNECT, hostname, port));
}

int             Client::getServerFd(void) const { return (this->getConnectingFd()); }

int             Client::getFd(void) const { return (this->fd); }

std::string     Client::getIp(void) const { return (this->ip); }

std::string     Client::getData(void) const { return (this->data); }

bool            Client::isConnected(void) const { return (this->connected); }


void            Client::setData(const std::string &data) { this->data.assign(data); }

void            Client::setConnected(const bool status) { this->connected = status; }

void            Client::setIp(const std::string &newIp) { this->ip = newIp; }

void            Client::setFd(const int newFd) { this->fd = newFd; }

