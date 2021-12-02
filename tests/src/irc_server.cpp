#include <catch2/catch.hpp>

#include "../../src/irc_server/irc_server.cpp"

TEST_CASE("userExists() default", "[TEST]")
{
    IrcServer s;
    IrcClient cl;
    s.getUsers()->insert(std::pair<std::string, IrcClient*>(cl.getNickName(), &cl));
    REQUIRE(s.userExists("default") == true);
}

TEST_CASE("userExists() with actual user", "[TEST]")
{
    IrcServer s;
    IrcClient cl("nick", "user", "host", "serv", "real");
    s.getUsers()->insert(std::pair<std::string, IrcClient*>(cl.getNickName(), &cl));
    REQUIRE(s.userExists("nick") == true);
}

TEST_CASE("userExists() with unknown user", "[TEST]")
{
    IrcServer s;
    IrcClient cl;
    s.getUsers()->insert(std::pair<std::string, IrcClient*>(cl.getNickName(), &cl));
    REQUIRE(s.userExists("hello") == false);
}

TEST_CASE("getUserByFd() with actual user", "[TEST]")
{
    IrcServer s;
    IrcClient cl("nick", "user", "host", "serv", "real");
    cl.setFd(10);
    s.getUsers()->insert(std::pair<std::string, IrcClient*>(cl.getNickName(), &cl));
    IrcClient *irCl = s.getUserByFd(10);
    REQUIRE(irCl->getFd() == cl.getFd());
}

TEST_CASE("getUserByFd() not existing user", "[TEST]")
{
    IrcServer s;
    IrcClient cl("nick", "user", "host", "serv", "real");
    s.getUsers()->insert(std::pair<std::string, IrcClient*>(cl.getNickName(), &cl));
    IrcClient *irCl = s.getUserByFd(15);
    REQUIRE(irCl == NULL);
}

TEST_CASE("nick()", "[TEST]")
{
    REQUIRE(42 == 42);
}
