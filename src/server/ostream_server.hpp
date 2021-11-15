#ifndef OSTREAM_SERVER_HPP
# define OSTREAM_SERVER_HPP

# include <iostream>

# include "server.hpp"
# include "../utils/colors.h"

std::ostream &operator << (std::ostream &output, const Server &s);

#endif
