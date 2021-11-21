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
    output << "server:> "  << "\n";
    
    if (s.getUsers()->size() > 0)
    {
        output << "ls users\n";
        putSpace(&output, 4);
        output << "NICK NAME";
        putSpace(&output, 4);
        output << "USER NAME";
        putSpace(&output, 4);
        output << "HOST NAME";
        putSpace(&output, 4);
        output << "SERV NAME";
        putSpace(&output, 4);
        output << "REAL NAME";
        putSpace(&output, 4);
        output << " STATUS\n";
        output << "    -------------------------------------------"; 
        output << "-------------------------------------------\n";
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
    if (s.getServer().getMessages()->size() > 0)
    {
        output << "\nMessages:\n";
        std::vector<Message*>::iterator iBegin;
        std::vector<Message*>::iterator iEnd;
        iBegin  = s.getServer().getMessages()->begin();
        iEnd = s.getServer().getMessages()->end();
        while (iBegin != iEnd)
        {
            Message *msg =  *iBegin;
            output << msg->getData() << "\n";
            iBegin++;
        }

    }
	return (output);
}
