#include "ostream_client.hpp"
#include <sstream>

std::ostream &operator << (std::ostream &output , const Client &cl)
{
	output << "Client {\n";
    if (cl.isConnected())
        output << "          STATUS:    " << GREEN << "connected" << RESET << std::endl;
    else
        output << "          STATUS:    " << RED << "disconnected" << RESET << std::endl;
    output << "          FD:        " << cl.getFd() << std::endl;
    output << "          IP:        " << cl.getIp() << std::endl;
    if (!cl.getData().empty())
    {
        std::istringstream ss(cl.getData());
        std::string del;
        output << "          DATA:      ";
        getline(ss, del, '\n');
        output << del << '\n';
        while(getline(ss, del, '\n'))
            output << "                     " << del << '\n';

    }
    output << "}" << std::endl << std::endl;
	return (output);
}
