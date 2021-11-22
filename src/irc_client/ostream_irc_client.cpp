#include "ostream_irc_client.hpp"
#include <sstream>

std::ostream &operator << (std::ostream &output , const IrcClient &cl)
{
    output << cl.getNickName() << " | " << cl.getUserName() << " | " << cl.getHostName() << " | "
            << cl.getServerName() << " | " << cl.getRealName() << "| " << "connected" << std::endl;
    return (output);
}
