#include "server/server.hpp"

#include <iostream>

int     main(void)
{
    Server s("8080");
    s.initTcpConnection();
    s.start();
    return (0);
}
