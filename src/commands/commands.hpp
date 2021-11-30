#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "../irc_server/irc_server.hpp"

#include "../tcp_connection/tcp_utils.hpp"

# define NICK_MAX_LEN 9
# define RPL_WELCOME "001"
# define RPL_WHOISUSER "311"
# define ERR_NOSUCHNICK "401"
# define ERR_NOTEXTTOSEND "412"
# define ERR_NONICKNAMEGIVEN "431"
# define ERR_ERRONEUSNICKNAME "432"
# define ERR_NICKNAMEINUSE "433"

std::string     nick(IrcServer *s, std::vector<Message*>::iterator lastMsg);
std::string     userMode(IrcServer *s, std::vector<Message*>::iterator lastMsg);
std::string     pong(IrcServer *s, std::vector<Message*>::iterator lastMsg);
std::string     privMsg(IrcServer *s, std::vector<Message*>::iterator lastMsg);
std::string     user(IrcServer *s, std::vector<Message*>::iterator lastMsg);
std::string     whoIs(IrcServer *s, std::vector<Message*>::iterator lastMsg);
std::string     unknown(IrcServer *s,std::vector<Message*>::iterator lastMsg);

#endif
