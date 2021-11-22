#include "ostream_irc_client.hpp"
#include <sstream>

static  void    putSpace(std::ostream &output, int nbSpaces)
{
    for (int i = 0; i <= nbSpaces; i++)
        output << " ";
}

static void     putStr(std::ostream &output, std::string str)
{
    if (str.empty())
    {
        output << "N/A";
    }
    else
    {
        output << str ;
    }
}

std::ostream &operator << (std::ostream &output , const IrcClient &cl)
{
    putSpace(output, 4);
    if (!cl.getNickName().empty())
    {
        output << cl.getNickName();
        putSpace(output, 5);
    }
    else
    {
        putStr(output, "N/A");
        putSpace(output, 10);
    }
    if (!cl.getUserName().empty())
    {
        putStr(output, cl.getUserName());
        putSpace(output, 5);
    }
    else
    {
        putStr(output, "N/A");
        putSpace(output, 10);
    }
    if (!cl.getHostName().empty())
    {
        putStr(output, cl.getHostName());
        putSpace(output, 5);
    }
    else
    {
        putStr(output, "N/A");
        putSpace(output, 10);
    }
    if (!cl.getServerName().empty())
    {
        putStr(output, cl.getServerName());
        putSpace(output, 5);
    }
    else
    {
        putStr(output, "N/A");
        putSpace(output, 10);
    }
    if (!cl.getRealName().empty())
    {
        putStr(output, cl.getRealName());
        putSpace(output, 5);
    }
    else
    {
        putStr(output, "N/A");
        putSpace(output, 7);
    }
    if (cl.isConnected())
    {
        putStr(output, "connected");
    }
    output << std::endl;
    return (output);
}
