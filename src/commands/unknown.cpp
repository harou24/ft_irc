#include "commands.hpp"

std::string unknown(IrcServer *s, std::vector<Message*>::iterator cmd)
{
    std::string reply;
    t_unknown unknown = (*cmd)->getCmd().getUnknown();
    reply.assign(unknown.error);
    s->getServer();
    return (reply);
}
