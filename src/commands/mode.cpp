#include "commands.hpp"

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
