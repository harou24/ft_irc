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
                    src/client/ostream_client.cpp)

add_executable(server.out apps/server.cpp
                            src/server/server.cpp                
                            src/tcp_connection/tcp_connection.cpp
                            src/tcp_connection/tcp_utils.cpp
                            src/tcp_connection/tcp_exceptions.cpp
                            src/client/client.cpp 
                            src/client/ostream_client.cpp)

add_executable(client.out apps/mock_client.cpp
                            src/tcp_connection/tcp_connection.cpp
                            src/tcp_connection/tcp_utils.cpp
                            src/tcp_connection/tcp_exceptions.cpp
                            src/client/client.cpp 
                            src/client/ostream_client.cpp
                            src/mock_client/mock_client.cpp)

include(CTest)
include(FetchContent)
add_subdirectory(tests)
