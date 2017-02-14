#
cmake_minimum_required(VERSION 2.8)

# this would direct cmake to override the compiler
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(PROJECT_NAME myproject)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall --std=gnu99 -lpthread")

add_library(csappLib csapp.cpp)
add_executable(echoclient echoclient.c)
add_executable(echoserver echoserver.c)

target_link_libraries(echoclient csappLib)
target_link_libraries(echoserver csappLib)

