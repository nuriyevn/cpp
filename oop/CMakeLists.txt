cmake_minimum_required(VERSION 3.17)

project(oop)

add_subdirectory(classes)
add_executable(virtual_static virtual_static.cpp)
add_executable(virtual virtual.cpp)