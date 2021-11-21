#include <catch2/catch.hpp>

#include <iostream>

#include "../../src/parser/parser.hpp"

TEST_CASE("strsplit(void)", "[PARSER]")
{
    Parser p("token1 token2 token3");
    std::vector tokens = p.split();
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens.at(0) == "token1");
    REQUIRE(tokens.at(1) == "token2");
    REQUIRE(tokens.at(2) == "token3");
}

TEST_CASE("strsplit(string str)", "[PARSER]")
{
    Parser p;
    std::vector tokens = p.split("token1 token2 token3");
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens.at(0) == "token1");
    REQUIRE(tokens.at(1) == "token2");
    REQUIRE(tokens.at(2) == "token3");
}

TEST_CASE("strsplit(string str, char c)", "[PARSER]")
{
    Parser p;
    std::vector tokens = p.split("token1|token2 | token3 |", '|');
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens.at(0) == "token1");
    REQUIRE(tokens.at(1) == "token2 ");
    REQUIRE(tokens.at(2) == " token3 ");
}

TEST_CASE("strsplit(string str, char c) with irc message", "[PARSER]")
{
    Parser p;
    std::string test = "CAP LS\nNICK haachtch\nUSER haachtch haachtch 127.0.0.1 :Haroutioun Achtchian";
    std::vector tokens = p.split(test, '\n');
    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens.at(0) == "CAP LS");
    REQUIRE(tokens.at(1) == "NICK haachtch");
    REQUIRE(tokens.at(2) == "USER haachtch haachtch 127.0.0.1 :Haroutioun Achtchian");
}
