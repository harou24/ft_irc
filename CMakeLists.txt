cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -fsanitize=address")

project(ft_irc VERSION 1.0)

include_directories(src/server)

include(CTest)
include(FetchContent)

add_subdirectory(tests)

add_executable(server.out app/server.cpp
                src/server/server.cpp
                src/tcp_connection/tcp_utils.cpp
                src/tcp_connection/tcp_exceptions.cpp
                src/client/client.cpp
                src/mock_client/mock_client.cpp
                src/tcp_connection/tcp_connection.cpp)

add_executable(client.out app/mock_client.cpp
                src/server/server.cpp
                src/tcp_connection/tcp_utils.cpp
                src/tcp_connection/tcp_exceptions.cpp
                src/client/client.cpp
                src/mock_client/mock_client.cpp
                src/tcp_connection/tcp_connection.cpp)
