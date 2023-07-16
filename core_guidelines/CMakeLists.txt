cmake_minimum_required(VERSION 3.17)

project(ERULES)

add_subdirectory(third)
add_executable(copy_elision copy_elision.cpp)