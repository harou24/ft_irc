#include "../src/server/server.hpp"

#include <iostream>

int     main(void)
{
    Server s("8080");
    s.start();
    return (0);
}
