#include "commands.hpp"

static std::string  getErrNickNameInUse(const std::string &nickName)
{
    return (":" + getHostName() + " " + ERR_NICKNAMEINUSE
                + " * " + nickName + " :NickName is already in use.\n");
}

static std::string getErrNoNickNameGiven(void)
{
    return (":" + getHostName() + " " + ERR_NONICKNAMEGIVEN
                + " * * "  + " :NickName is not given.\n");
}

static std::string getErrInvalidNick(void)
{
    return (":" + getHostName() + " " + ERR_ERRONEUSNICKNAME
                + " * * "  + " :NickName is not valid.\n");
}

static std::string  execNick(IrcServer *s,
                                std::vector<Message*>::iterator cmd,
                                         const std::string &nickName)
{
    std::string reply;

    Client *c = (*cmd)->getSender();
    IrcClient *cl = s->getUserByFd(c->getFd());
    if (cl == NULL)
    {
        cl = new IrcClient(c, nickName);
        s->addUser(nickName, cl);
        reply = ":" + getHostName() + " " + RPL_WELCOME + " " + nickName
                + " :Welcome to irc server.\n";
    }
    else
    {
        cl = s->removeUser(cl->getNickName());
        s->addUser(nickName, cl);
        reply += ":" + cl->getNickName() + " NICK " + nickName + "\n";
        cl->setNickName(nickName);
    }
    return (reply);
}

std::string    nick(IrcServer *s, std::vector<Message*>::iterator cmd)
{
        t_nick nick = (*cmd)->getCmd().getNick();
	std::cout << "FUCKING NICKNAME->" << "|" << nick.nickName << "|" << std::endl;
        if (s->isNickInUse(nick.nickName))
            return (getErrNickNameInUse(nick.nickName));
        if (nick.nickName.empty())
            return (getErrNoNickNameGiven());
        if (nick.nickName.size() > NICK_MAX_LEN)
            return (getErrInvalidNick());
        return (execNick(s, cmd, nick.nickName));
}
