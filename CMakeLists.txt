cmake_minimum_required(VERSION 3.0)
project("Tic Tac Toe Online" VERSION 0.1)

add_compile_options(-Wall)

add_executable(
    client
    client/main.cpp
    common/message.cpp
)

add_executable(
    server
    server/main.cpp
    server/grid.cpp
    server/game.cpp
    common/message.cpp
)

target_include_directories(client PRIVATE common)
target_include_directories(server PRIVATE common)