#include "../src/mock_client/mock_client.hpp"

#include <stdlib.h>

int     main(int argc, char **argv)
{
    if (argc != 3)
        return (EXIT_FAILURE);
    MockClient cl(argv[1], argv[2]);
    cl.connectToServer();
    cl.runCommunicationWithServer();
    return (EXIT_SUCCESS);
}
