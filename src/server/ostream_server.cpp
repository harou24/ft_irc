#include "ostream_server.hpp"
#include "ostream_client.hpp"

#include <sstream>

static  void    putSpace(std::ostream *output, int nbSpaces)
{
    for (int i = 0; i <= nbSpaces; i++)
        *output << " ";
}

std::ostream &operator << (std::ostream &output , const Server &s)
{
    output << "---------Server";
    putSpace(&output, 2);
    output  << s.getLocalTime() << std::endl;
    output << "NB_CONNECTED:      " << s.getNbConnectedClients() << std::endl;
    output << "CONNECTED_CLIENTS: "  << std::endl;
    if (s.getClients()->size() > 0)
    {
        putSpace(&output, 5);
        std::map<int, Client*>::iterator it;
        for (it = s.getClients()->begin(); it != s.getClients()->end(); it++)
            output  << *(it->second);
    }
    output << "\n";
	return (output);
}
