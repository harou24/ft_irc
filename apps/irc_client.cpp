#include "../src/irc_client/irc_client.hpp"

#include <stdlib.h>

int     main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "NB ARG error !\n";
        return (1);
    }
    IrcClient cl(argv[1], argv[2]);
    cl.connectToServer();
    cl.runCommunicationWithServer();
    return (0);
}
