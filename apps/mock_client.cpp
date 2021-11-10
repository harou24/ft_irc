#include "../src/mock_client/mock_client.hpp"

int     main(int argc, char **argv)
{
    if (argc != 3)
        return (EXIT_FAILURE);
    MockClient cl;
    cl.connectToServer(argv[1], argv[2]);
    return (EXIT_SUCCESS);
}
