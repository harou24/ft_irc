#include "ostream_irc_server.hpp"
#include "../utils/output_utils.hpp"
#include "../irc_client/ostream_irc_client.hpp"

#include <sstream>
#include <map>

std::ostream &operator << (std::ostream &output , IrcServer &s)
{
    
    if (s.getUsers()->size() > 0)
    {
        output << BLUB  << s.getServer().getLocalTime().substr(0, 5) << "-server :>"  << RESET;
        output << " ls users\n\n";
        putChar(output, ' ', 5);
        output << "NICK NAME";
        putChar(output, ' ', 5);
        output << "USER NAME";
        putChar(output, ' ', 5);
        output << "HOST NAME";
        putChar(output, ' ', 5);
        output << "SERV NAME";
        putChar(output, ' ', 7);
        output << "REAL NAME";
        putChar(output, ' ', 14);
        output << " STATUS\n";
        putChar(output, ' ', 5);
        putChar(output, '-', 91);
        putChar(output, '\n', 1);
        std::map<std::string, IrcClient*>::iterator itBegin;
        std::map<std::string, IrcClient*>::iterator itEnd;
        itBegin = s.getUsers()->begin();
        itEnd = s.getUsers()->end();
        while (itBegin != itEnd)
        {
            output << *(itBegin->second) << '\n';
            itBegin++;
        }
    }
    if (s.getServer().getClients()->size() > 0)
    {
        output << "\n\n";
        putChar(output, ' ', 5);
        output << "FD";
        putChar(output, ' ', 6);
        output << "DATA SENT\n";
        putChar(output, ' ', 5);
        putChar(output, '-', 91);
        putChar(output, '\n', 1);
        std::map<int, Client*>::iterator iBegin;
        std::map<int, Client*>::iterator iEnd;
        iBegin  = s.getServer().getClients()->begin();
        iEnd = s.getServer().getClients()->end();
        while (iBegin != iEnd)
        {
            Client *c =  (*iBegin).second;
            putChar(output, ' ', 5);
            output << c->getFd();
            putChar(output, ' ', 5);
            output << c->getData() << "\n";
            iBegin++;
        }
    }
    output << std::endl;
    if (s.getServer().getMessages()->size() > 0)
    {
        output << "\n\n";
        putChar(output, ' ', 5);
        output << "TIME";
        putChar(output, ' ', 6);
        output << "SENT BY";
        putChar(output, ' ', 6);
        output << "MESSAGES\n";
        putChar(output, ' ', 5);
        putChar(output, '-', 91);
        putChar(output, '\n', 1);
        std::vector<Message*>::iterator iBegin;
        std::vector<Message*>::iterator iEnd;
        iBegin  = s.getServer().getMessages()->begin();
        iEnd = s.getServer().getMessages()->end();
        while (iBegin != iEnd)
        {
            Message *msg =  *iBegin;
            putChar(output, ' ', 5);
            output << msg->getTime().substr(0, 5);
            putChar(output, ' ', 5);
            IrcClient *cl = s.getUserByFd(msg->getSender().getFd());
            if (cl != NULL)
                output << GREEN << cl->getNickName() << RESET;
            putChar(output, ' ', 5);
            output << msg->getData() << "\n";
            iBegin++;
        }
        output << std::endl;
    }
	return (output);
}
