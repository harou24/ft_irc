#include "tcp_exceptions.hpp"

const char* TcpException::what() const throw()
{
    return ("Error : Tcp connection error @_@");
}

const char* TcpAcceptException::what() const throw()
{
    return ("Error : accept() function failed !");
}

TcpGetAddrInfoException::TcpGetAddrInfoException(const char *error)
{
    this->errorInfo.assign(error);
}

TcpGetAddrInfoException::~TcpGetAddrInfoException() throw() {}

const char* TcpGetAddrInfoException::what() const throw()
{
    return ("Error : getaddrinfo() function failed !");
}
