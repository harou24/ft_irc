#include "output_utils.hpp"

void    putChar(std::ostream &output, const char c, size_t nbTimes)
{
    for (size_t i = 0; i < nbTimes; i++)
        output << c;
}
