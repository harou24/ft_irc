add_executable(server.out server.cpp)
target_link_libraries(server.out PRIVATE ft_irc)

add_executable(irc_server.out irc_server.cpp)
target_link_libraries(irc_server.out PRIVATE ft_irc)

add_executable(mock_client.out mock_client.cpp)
target_link_libraries(mock_client.out PRIVATE ft_irc)

add_executable(irc_client.out irc_client.cpp)
target_link_libraries(irc_client.out PRIVATE ft_irc)
