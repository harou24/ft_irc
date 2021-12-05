# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(ft_irc LANGUAGES CXX)

# require C++11
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -fsanitize=address")

# include header files
include_directories(src/server)
include_directories(src/client)

# example library
add_library(ft_irc src/server/server.cpp
                    src/tcp_connection/tcp_connection.cpp
                    src/tcp_connection/tcp_utils.cpp
                    src/tcp_connection/tcp_exceptions.cpp
                    src/client/client.cpp 
                    src/mock_client/mock_client.cpp 
                    src/mock_server/mock_server.cpp 
                    src/irc_server/irc_server.cpp 
                    src/server/ostream_server.cpp 
                    src/irc_server/ostream_irc_server.cpp 
                    src/irc_client/irc_client.cpp 
                    src/client/ostream_client.cpp
                    src/irc_client/ostream_irc_client.cpp
                    src/utils/output_utils.cpp
                    src/cmd_parser/cmd_parser.cpp
                    src/message/message.cpp
                    src/commands/nick.cpp
                    src/commands/user.cpp
                    src/commands/mode.cpp
                    src/commands/priv_msg.cpp
                    src/commands/who_is.cpp
                    src/commands/join.cpp
                    src/commands/pong.cpp
                    src/commands/unknown.cpp
                    src/channel/channel.cpp
                    src/parser/parser.cpp)

add_subdirectory(apps)
include(CTest)
include(FetchContent)
add_subdirectory(tests)
