#include <catch2/catch.hpp>

#include "../../src/irc_server/irc_server.cpp"

TEST_CASE("userExists() with unknown user", "[TEST]")
{
    IrcServer s;
    IrcClient cl;
    s.getUsers()->insert(std::pair<std::string, IrcClient*>(cl.getNickName(), &cl));
    REQUIRE(s.userExists("hello") == false);
}

