cmake_minimum_required(VERSION 2.5)

set(PROJECT_NAME my_project)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g --std=gnu99 -Wall")

add_executable(run format.c)

