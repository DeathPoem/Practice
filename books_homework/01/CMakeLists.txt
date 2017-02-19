#
cmake_minimum_required(VERSION 2.8)

# this would direct cmake to override the compiler
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(PROJECT_NAME myproject)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wno-write-strings -Wno-sign-compare --std=gnu99 -lpthread")

add_library(csappLib csapp.c)
add_executable(echoclient echoclient.c)
add_executable(echoserver echoserver.c)
add_executable(tinyhttpserver tinyhttp.c)
add_executable(tinyhttpclient tinyhttpclient.c)

target_link_libraries(echoclient csappLib)
target_link_libraries(echoclient pthread)
target_link_libraries(echoserver csappLib)
target_link_libraries(echoserver pthread)

target_link_libraries(tinyhttpserver csappLib)
target_link_libraries(tinyhttpserver pthread)
target_link_libraries(tinyhttpclient csappLib)
target_link_libraries(tinyhttpclient pthread)
