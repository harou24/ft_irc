cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ft_irc VERSION 1.0)

include_directories(src/server)

add_executable(server.out app/main.cpp
                src/server/server.cpp
                src/server/server_utils.cpp
                src/client/client.cpp
                src/tcp_connection/tcp_connection.cpp)
            
#target_include_directories(ft_irc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/server)
