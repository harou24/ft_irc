#include "commands.hpp"

std::string join(IrcServer *s, std::vector<Message*>::iterator cmd)
{
    std::string reply;
    t_join join = (*cmd)->getCmd().getJoin();
    Client *c = (*cmd)->getSender();
    IrcClient *cl = s->getUserByFd(c->getFd());
    if (!cl)
        return ("");
    Channel *channel;
    if (!s->channelExists(join.channelName))
    {
        channel = new Channel(join.channelName, cl);
        channel->addUser(cl);
        s->addChannel(join.channelName, channel);
        reply = join.channelName + " :No topic is set.\n";
    }
    else
    {
        channel = s->getChannel(join.channelName);
        channel->addUser(cl);
        reply = join.channelName + " :" + channel->getTopic() + "\n";
    }
    channel->debug();
    return (reply);
}