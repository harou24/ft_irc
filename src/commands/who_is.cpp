#include "commands.hpp"

std::string whoIs(IrcServer *s, std::vector<Message*>::iterator cmd)
{
    std::string reply;
    Client *c = (*cmd)->getSender();
    IrcClient *cl = s->getUserByFd(c->getFd());
    t_whoIs who = (*cmd)->getCmd().getWhoIs();
    reply = cl->getNickName() + " " + cl->getUserName() + " " + cl->getHostName() + " * :" + cl->getRealName() + "\n";
    return (reply);
}
