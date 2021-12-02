#ifndef OSTREAM_IRC_CLIENT_HPP
# define OSTREAM_IRC_CLIENT_HPP

# include <iostream>

# include "irc_client.hpp"
# include "../utils/colors.h"

std::ostream &operator << (std::ostream &output, const IrcClient &cl);

#endif
