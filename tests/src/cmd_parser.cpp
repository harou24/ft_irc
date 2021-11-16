#include <catch2/catch.hpp>

#include <iostream>

#include "../../src/cmd_parser/cmd_parser.hpp"

TEST_CASE("PRIVMSG type", "[CMD_PARSER]")
{
    CmdParser cmd("PRIVMSG hello :this is the message");
    REQUIRE(cmd.getType() == PRIVMSG);
}

TEST_CASE("NICK type", "[CMD_PARSER]")
{
    CmdParser cmd("NICK");
    REQUIRE(cmd.getType() == NICK);
}

TEST_CASE("UNKNOWN type", "[CMD_PARSER]")
{
    CmdParser cmd("hello");
    REQUIRE(cmd.getType() == UNKNOWN);
}

TEST_CASE("USER type", "[CMD_PARSER]")
{
    CmdParser cmd("USER hello hello 127.0.0.1 :Real Name");
    REQUIRE(cmd.getType() == USER);
}

TEST_CASE("test if cmd str is splited correctly in tokens", "[CMD_PARSER]")
{
    CmdParser cmd("PRIVMSG hello :this is the message");
    REQUIRE(cmd.getTokens()[0] == "PRIVMSG");
    REQUIRE(cmd.getTokens()[1] == "hello");
    REQUIRE(cmd.getTokens()[2] == ":this is the message");
}

TEST_CASE("getUser()", "[CMD_PARSER]")
{
    CmdParser cmd("USER hello hello 127.0.0.1 :Real Name");
    REQUIRE(cmd.getType() == USER);
    t_user usr = cmd.getUser();
    REQUIRE(usr.userName == "hello");
    REQUIRE(usr.hostName == "hello");
    REQUIRE(usr.serverName == "127.0.0.1");
    REQUIRE(usr.realName == "Real Name");
}
