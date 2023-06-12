cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 14)
project(cpp_top_level)
add_subdirectory(templates)

add_executable(program3 3.cpp)