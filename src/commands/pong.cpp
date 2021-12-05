#include "commands.hpp"

std::string     pong(IrcServer *s, std::vector<Message*>::iterator cmd)
{
    t_ping ping = (*cmd)->getCmd().getPing();
    std::string reply;
    Client *c = (*cmd)->getSender();
    IrcClient *cl = s->getUserByFd(c->getFd());
    if (!cl)
        return (reply);
    reply = "PONG " + ping.hostName + "\n";
    return (reply);
}
