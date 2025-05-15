cmake_minimum_required(VERSION 3.31)
project(key_value_store)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# add the testing library catch2
enable_testing()
add_library(catch2_main lib/catch2_main.cpp
        include/Database.h)
target_include_directories(catch2_main PUBLIC lib)
# link the library so that other programs can get it
link_libraries(catch2_main)


add_library(server src/Server.cpp)
add_library(command_handler src/CommandHandler.cpp)
add_library(database src/Database.cpp)
link_libraries(server command_handler database)

add_executable(key_value_store src/main.cpp)

# TESTS
add_executable(test_command_handler test/test_command_handler.cpp)
add_test(test_command_handler test_command_handler)
