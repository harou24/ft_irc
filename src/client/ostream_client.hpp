#ifndef OSTREAM_CLIENT_HPP
# define OSTREAM_CLIENT_HPP

# include <iostream>

# include "client.hpp"
# include "../utils/colors.h"

std::ostream &operator << (std::ostream &output, const Client &cl);

#endif
