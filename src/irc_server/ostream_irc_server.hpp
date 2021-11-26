#ifndef OSTREAM_IRC_SERVER_HPP
# define OSTREAM_IRC_SERVER_HPP

# include <iostream>

# include "irc_server.hpp"
# include "../utils/colors.h"

std::ostream &operator << (std::ostream &output, IrcServer &s);


#endif
