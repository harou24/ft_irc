#include "ostream_client.hpp"
#include <sstream>

std::ostream &operator << (std::ostream &output , const Server &s)
{
    output << "-------------------Server-------------------" << std::endl << std::endl;
    output << "Connected clients : " << s.nbConnectedClients << std::endl;
    for (int i = 0; i < s.nbConnectedClients; i++)
    {
        output << s.clients.at(i)
    }
	return (output);
}
