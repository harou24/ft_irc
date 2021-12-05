#include "commands.hpp"

std::string    user(IrcServer *s, std::vector<Message*>::iterator cmd)
{
    std::string reply;
    t_user user = (*cmd)->getCmd().getUser();
    Client *c = (*cmd)->getSender();
    IrcClient *cl = s->getUserByFd(c->getFd());
    if (cl)
    {
        cl->setUserName(user.userName);
        cl->setHostName(user.hostName);
        cl->setServerName(user.serverName);
        cl->setRealName(user.realName);
    }
    return (reply);
}
