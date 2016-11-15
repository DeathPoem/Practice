#
cmake_minimum_required(3.5)

#
project(echo)

add_executable(echo, main.c server.c)

#set(CMAKE_CXX_FLAGS "-g -Wall --std=c++11")
