#ifndef TCP_CONNECTION_HPP
# define TCP_CONNECTION_HPP

# include "../client/client.hpp"

# include <stdexcept>

class TcpConnection {
    private:
        const char  *port;
        fd_set      masterFds;
        fd_set      readFds;
        int         listenerFd;
        int         fdMax;

    public:
        TcpConnection(void);
        TcpConnection(const char *port);
        ~TcpConnection(void);

        void            init(void);
        void            acceptClientConnection(Client &cl);
        std::string     getDataFromFd(int fd);
        void            updateFdsInSet();

        fd_set          *getMasterFds(void);
        fd_set          *getReadFds(void);
        int             getListenerFd(void) const;
        int             getFdMax(void) const;

        void            setFdMax(const int newMax);

        bool            isFdReadyForCommunication(const int fd);

        class TcpAcceptException : public std::exception
			{
				public :
						TcpAcceptException(void);
						TcpAcceptException(const TcpAcceptException &cpy);
						~TcpAcceptException(void) throw();

						TcpAcceptException& operator = (const TcpAcceptException &old);

						virtual const char* what() const throw();
			};
};

#endif
