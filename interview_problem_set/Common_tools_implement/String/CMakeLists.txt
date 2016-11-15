cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME stringtest)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g --std=c++11 -Wall")

add_library(library string.cpp)
add_executable(run test.cpp)

target_link_libraries(run library)
