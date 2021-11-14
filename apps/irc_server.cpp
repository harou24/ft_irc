#include "../src/irc_server/irc_server.hpp"

#include <iostream>

int     main(void)
{
    IrcServer s("8080");
    s.start();
    return (0);
}
