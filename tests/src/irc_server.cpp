#include <catch2/catch.hpp>

#include "../../src/irc_server/irc_server.cpp"

TEST_CASE("Running IrcServ Once", "[TEST]")
{
	IrcServer irc("8080");
	irc.init();
	irc.runOnce();
}

