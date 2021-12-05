#include "commands.hpp"

std::string privMsg(IrcServer *s, std::vector<Message*>::iterator cmd)
{
    std::string reply;
    t_privMsg privMsg = (*cmd)->getCmd().getPrivMsg();
    IrcClient *sender = s->getUserByFd((*cmd)->getSender()->getFd());
    if (!s->isNickInUse(privMsg.nickName))
        return privMsg.nickName + " :No such nick\n";
    if (s->isNickInUse(privMsg.nickName) && !s->getUsers()->find(privMsg.nickName)->second->getClient()->isConnected())
        return  privMsg.nickName + ": not available, try again later.\n";
    if (s->isNickInUse(privMsg.nickName))
    {
        reply = ":" + sender->getNickName() + "!" + sender->getNickName() + "@" + sender->getServerName()
                + "PRIVMSG " + privMsg.nickName + " " + privMsg.msg + "\n";
        s->getServer().sendMsg(s->getUsers()->find(privMsg.nickName)->second->getClient()->getFd(), reply);
    }
    return ("");
}
