cmake_minimum_required(VERSION 3.10)
project(ft_irc)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -fsanitize=address")

include_directories(src)
include(CTest)
include(FetchContent)

add_subdirectory(src)
add_subdirectory(tests)
add_executable(irc_server.exe src/main.cpp)
