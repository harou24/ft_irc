#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <iostream>
#include <string.h>
#include <unistd.h>

#include "client.hpp"
#include "ostream_client.hpp"

#define TEST_BUFF_SIZE  256

TEST_CASE("Send Data", "[CLIENT]")
{
    Client cl;
    std::cout << cl;
//    int fdToSendTo = 4;
//    std::string dataToSend("HelloWorld\n");
//    cl.sendMsg(fdToSendTo, dataToSend);

//    char    buff[TEST_BUFF_SIZE];
//    memset(buff, 0, TEST_BUFF_SIZE);
//    int nbBytes = read(fdToSendTo, buff, TEST_BUFF_SIZE);
//    buff[nbBytes] = '\0';
    //std::string dataRead(buff);
   // REQUIRE(dataToSend == dataRead);
}
