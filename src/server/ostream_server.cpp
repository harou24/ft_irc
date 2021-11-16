#include "ostream_server.hpp"
#include "ostream_client.hpp"

#include <sstream>

std::ostream &operator << (std::ostream &output , const Server &s)
{
    output << "Server {\n";
    output << "                 DATE:              " << s.getLocalTime();
    output << "                 NB_CONNECTED:      " << s.getNbConnectedClients() << std::endl;
    output << "                 CLIENTS:           "  << std::endl;
    if (s.getClients()->size() > 0)
        output << "                      " << *(s.getClients()->at(5));
    output << "}\n";
	return (output);
}
