#include "commands.hpp"

static std::string getNickErrorReply(IrcServer *s, t_nick nick)
{
    std::string reply;
    if (nick.nickName.empty())
        reply = ":" + getHostName() + " " + ERR_NONICKNAMEGIVEN
                    + " * * "  + " :NickName is not given.\n";
    else if (nick.nickName.size() > NICK_MAX_LEN)
        reply = ":" + getHostName() + " " + ERR_ERRONEUSNICKNAME
                    + " * * "  + " :NickName is not valid.\n";
    else if (s->isNickInUse(nick.nickName))
        reply = ":" + getHostName() + " " + ERR_NICKNAMEINUSE
                    + " * " + nick.nickName + " :NickName is already in use.\n";
    return (reply);
}

std::string    nick(IrcServer *s, std::vector<Message*>::iterator cmd)
{
        std::string reply;
        t_nick nick = (*cmd)->getCmd().getNick();

        Client *c = (*cmd)->getSender();
        IrcClient *cl = s->getUserByFd(c->getFd());

        if (s->isNickInUse(nick.nickName))
        {
            //need to disconnect client here after returning
            return (getNickErrorReply(s, nick));
        }
        if (cl == NULL)
        {
            cl = new IrcClient(c, nick.nickName);
            s->addUser(nick.nickName, cl);
            reply = ":" + getHostName() + " " + RPL_WELCOME + " " + nick.nickName + " :Welcome to irc server.\n";
        }
        else
        {
            cl = s->removeUser(cl->getNickName());
            s->addUser(nick.nickName, cl);
            reply += ":" + cl->getNickName() + " NICK " + nick.nickName + "\n";
            cl->setNickName(nick.nickName);
        }
        return (reply);
}
