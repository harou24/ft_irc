#include "commands.hpp"
#include "../utils/colors.h"
#include "../client/ostream_client.hpp"

#include <unistd.h>

#include "../irc_client/ostream_irc_client.cpp"

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

std::string    userMode(IrcServer *s, std::vector<Message*>::iterator cmd)
{
    std::string reply;
    t_userMode userMode = (*cmd)->getCmd().getUserMode();
    if (s->getUsers()->find(userMode.nickName) != s->getUsers()->end())
    {
        reply = "MODE " + userMode.nickName + " " + userMode.mode + "\n";
    }
    return (reply);
}

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

std::string whoIs(IrcServer *s, std::vector<Message*>::iterator cmd)
{
    std::string reply;
    Client *c = (*cmd)->getSender();
    IrcClient *cl = s->getUserByFd(c->getFd());
    t_whoIs who = (*cmd)->getCmd().getWhoIs();
    reply = cl->getNickName() + " " + cl->getUserName() + " " + cl->getHostName() + " * :" + cl->getRealName() + "\n";
    std::cerr << RED << reply << RESET << std::endl;
    return (reply);
}

std::string unknown(IrcServer *s, std::vector<Message*>::iterator cmd)
{
    std::string reply;
    t_unknown unknown = (*cmd)->getCmd().getUnknown();
    reply.assign(unknown.error);
    s->getServer();
    return (reply);
}
