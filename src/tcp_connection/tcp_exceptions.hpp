#ifndef TCP_EXCEPTIONS_HPP
# define TCP_EXCEPTIONS_HPP

# include <iostream>
# include <stdexcept>

class TcpException : public std::exception {
    public:
        virtual const char* what() const throw();
};

class TcpAcceptException: public std::exception {
    public:
        virtual const char* what() const throw();
};

class TcpGetAddrInfoException: public std::exception {
    private:
        std::string errorInfo;

    public:
        TcpGetAddrInfoException(const char *errorInfo);
        virtual ~TcpGetAddrInfoException(void) throw ();

        virtual const char* what() const throw();
};

#endif
