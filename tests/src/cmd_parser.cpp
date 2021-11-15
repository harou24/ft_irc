#include <catch2/catch.hpp>

#include <iostream>

#include "../../src/cmd_parser/cmd_parser.hpp"

TEST_CASE("constructor", "[CMD_PARSER]")
{
    CmdParser cmd("PRIVMSG nickname :hello how are you");
    REQUIRE(cmd.getType() == PRIVMSG);
    REQUIRE(cmd.getNickName() == "nickname");
    REQUIRE(cmd.getMsg() == "hello how are you");
}

