#include <catch2/catch.hpp>

#include "../../src/irc_client/irc_client.hpp"

TEST_CASE("test Irc_client copy constructor with Client type", "[IRC_CLIENT]")
{
    Client cl(5);
    IrcClient cll(cl);
    REQUIRE(cll.isConnected() == false);
    REQUIRE(cll.getFd() == 5);
}
