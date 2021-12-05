#include "commands.hpp"

std::string join(IrcServer *s, std::vector<Message*>::iterator cmd)
{
    std::string reply;
    t_join join = (*cmd)->getCmd().getJoin();
    Client *c = (*cmd)->getSender();
    IrcClient *cl = s->getUserByFd(c->getFd());
    if (!cl)
        return ("");
    if (!s->channelExists(join.channelName))
    {
        Channel *channel = new Channel(join.channelName, cl);
        channel->addUser(cl);
        s->addChannel(join.channelName, channel);
        reply = join.channelName + " :No topic is set.\n";
    }
    else
    {
        Channel *channel = s->getChannel(join.channelName);
        channel->addUser(cl);
        reply = join.channelName + " :" + channel->getTopic() + "\n";
    }
    return (reply);
}
