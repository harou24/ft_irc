#include "server.hpp"
#include "server_utils.hpp"

Server::Server(void)
{
    this->port = "8080";
    zeroFdSet(&this->master);
    zeroFdSet(&this->readFds);
    this->listener = -1;
    this->fdMax = 0;
}

Server::Server(const char *port): port(port)
{
    zeroFdSet(&this->master);
    zeroFdSet(&this->readFds);
    this->listener = -1;
    this->fdMax = 0;
}
