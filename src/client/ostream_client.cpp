#include "ostream_client.hpp"
#include <sstream>

static  void    putSpace(std::ostream *output, int nbSpaces)
{
    for (int i = 0; i <= nbSpaces; i++)
        *output << " ";
}

std::ostream &operator << (std::ostream &output , const Client &cl)
{
	output <<"Client {\n";
    if (cl.isConnected())
    {
        putSpace(&output, 5);
        output << "STATUS:";
        putSpace(&output, 4);
        output << GREEN << "connected" << RESET << std::endl;
    }
    else
    {
        putSpace(&output, 5);
        output << "STATUS:";
        putSpace(&output, 4);
        output << RED << "disconnected" << RESET << std::endl;
    }
    putSpace(&output, 5);
    output << "FD:";
    putSpace(&output, 8);
    output << cl.getFd() << std::endl;
    putSpace(&output, 5);
    output << "IP:";
    putSpace(&output, 8);
    output << cl.getIp() << std::endl;
    if (!cl.getData().empty())
    {
        std::istringstream ss(cl.getData());
        std::string del;
        putSpace(&output, 5);
        output << "DATA:";
        putSpace(&output, 0);
        getline(ss, del, '\n');
        putSpace(&output, 5);
        output << del << '\n';
        while(getline(ss, del, '\n'))
        {
            putSpace(&output, 17);
            output << del << '\n';
        }
    }
    output << "}" << std::endl;
	return (output);
}
