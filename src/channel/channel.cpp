#include "channel.hpp"
#include "../utils/colors.h"

Channel::Channel(void)
{ 
    this->name = "default";
    this->chop = NULL;
    this->users = new std::vector<IrcClient*>();
    this->topic = "default";
    this->mode = "default";
}

Channel::Channel(const std::string &name)
{ 
    this->name = name;
    this->chop = NULL;
    this->users = new std::vector<IrcClient*>();
    this->topic = "default";
    this->mode = "default";
}

Channel::Channel(const std::string &name, IrcClient *op)
{ 
    this->name = name;
    this->chop = op;
    this->users = new std::vector<IrcClient*>();
    this->topic = "default";
    this->mode = "default";
}

Channel::~Channel(void) { }

void    Channel::addUser(IrcClient *cl)
{
    this->users->push_back(cl);
}

void    Channel::setName(const std::string &name)
{
    this->name = name;
}

void    Channel::setChop(IrcClient *op)
{
    this->chop = op;
}

void    Channel::setTopic(const std::string &topic)
{
    this->topic = topic;
}

void    Channel::setMode(const std::string &mode)
{
    this->mode = mode;
}

std::string Channel::getName(void) const { return (this->name); }

IrcClient*  Channel::getChop(void) const { return (this->chop); }

std::string Channel::getTopic(void) const { return (this->topic); }

std::string Channel::getMode(void) const { return (this->mode); }

void    Channel::debug(void) const
{
    std::cerr << "::CHANNEL_DEBUG::\n";
    std::cerr << RED << "NAME->" << GREEN << "|" << this->name << "|" << RESET << std::endl;
    std::cerr << RED << "OPERATOR->" << GREEN << "|" << this->chop->getNickName() << "|" << RESET << std::endl;
    std::cerr << RED << "TOPIC->" << GREEN << "|" << this->topic << "|" << RESET << std::endl;
    std::cerr << RED << "MODE->" << GREEN << "|" << this->mode << "|" << RESET << std::endl;
}
