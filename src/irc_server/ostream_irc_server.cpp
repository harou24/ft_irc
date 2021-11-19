#include "ostream_irc_server.hpp"
#include "../irc_client/ostream_irc_client.hpp"

#include <sstream>
#include <map>

static  void    putSpace(std::ostream *output, int nbSpaces)
{
    for (int i = 0; i <= nbSpaces; i++)
        *output << " ";
}

std::ostream &operator << (std::ostream &output , const IrcServer &s)
{
    output << "---------IRC-Server--------";
    putSpace(&output, 2);
    output  << s.getLocalTime() << std::endl;
    output << "NB_CONNECTED:      " << s.getNbConnectedClients() << std::endl;
    output << "CONNECTED_CLIENTS: "  << std::endl;
    if (s.getUsers()->size() > 0)
    {
        std::map<std::string, IrcClient*>::iterator it;
        for (it = s.getUsers()->begin(); it != s.getUsers()->end(); it++)
        {
            std::cout << it->first << "->" << *(it->second) << '\n';
        }
    }
    output << "\n";
	return (output);
}
