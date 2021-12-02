#include "ostream_irc_client.hpp"
#include "../utils/output_utils.hpp"

#include <sstream>

std::ostream &operator << (std::ostream &output , const IrcClient &cl)
{
    putChar(output, ' ', 5);
    if (cl.getClient().isConnected())
        output << GREEN;
    else
        output << RED;
    output<< cl.getNickName();
    output << RESET;
    putChar(output, ' ', 6); 
    output << cl.getUserName();
    putChar(output, ' ', 6);
    output << cl.getHostName();
    putChar(output, ' ', 6);
    output << cl.getServerName();
    putChar(output, ' ', 7);
    output << cl.getRealName();
    putChar(output, ' ', 4);
    if (cl.getClient().isConnected())
    {
        output << GREEN;
        output << "connected";
        output << RESET;
    }
    else
    {
        output << RED;
        output << "disconnected";
        output << RESET;
    }
    return (output);
}
