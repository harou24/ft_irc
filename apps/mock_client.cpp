#include "../src/mock_client/mock_client.hpp"

int     main(int argc, char **argv)
{
    if (argc != 3)
        return (EXIT_FAILURE);
    MockClient cl(argv[1], argv[2]);
    cl.connectToServer();
    return (EXIT_SUCCESS);
}
