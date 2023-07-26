cmake_minimum_required(VERSION 3.17)

project(ERULES)

add_subdirectory(third)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fno-elide-constructors")
add_executable(copy_elision copy_elision.cpp)