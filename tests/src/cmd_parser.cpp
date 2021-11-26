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
    REQUIRE(cmd.getTokens()[2] == "this is the message");
}

TEST_CASE("getNick()", "[CMD_PARSER]")
{
    CmdParser cmd("NICK nicky");
    REQUIRE(cmd.getType() == NICK);
    t_nick nick = cmd.getNick();
    REQUIRE(nick.nickName == "nicky");
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

TEST_CASE("getPrivMsg()", "[CMD_PARSER]")
{
    CmdParser cmd("PRIVMSG nickname :this is the message !");
    t_privMsg priv = cmd.getPrivMsg();
    REQUIRE(priv.nickName == "nickname");
    REQUIRE(priv.msg == "this is the message !");
}

TEST_CASE("getPrivMsg() with new line", "[CMD_PARSER]")
{
    CmdParser cmd("PRIVMSG nickname :this is the message !\n");
    t_privMsg priv = cmd.getPrivMsg();
    REQUIRE(priv.nickName == "nickname");
    REQUIRE(priv.msg == "this is the message !");
}

TEST_CASE("getPrivMsg() with spaces at the end", "[CMD_PARSER]")
{
    CmdParser cmd("PRIVMSG nickname :this is the message !                 ");
    t_privMsg priv = cmd.getPrivMsg();
    REQUIRE(priv.nickName == "nickname");
    REQUIRE(priv.msg == "this is the message !");
}

TEST_CASE("getUserMode()", "[CMD_PARSER]")
{
    CmdParser cmd("MODE nick +i");
    t_userMode mode = cmd.getUserMode();
    REQUIRE(cmd.getType() == MODE);
    REQUIRE(mode.nickName == "nick");
    REQUIRE(mode.mode == "+i");
}

TEST_CASE("getPing()", "[CMD_PARSER]")
{
    CmdParser cmd("PING hostName");
    t_ping ping = cmd.getPing();
    REQUIRE(cmd.getType() == PING);
    REQUIRE(ping.hostName == "hostName");
}

TEST_CASE("getUnknown()", "[CMD_PARSER]")
{
    CmdParser cmd("PRIVM :this is the message !");
    REQUIRE(cmd.getType() == UNKNOWN);
    t_unknown unknown = cmd.getUnknown();
    REQUIRE(!unknown.error.empty());
}

