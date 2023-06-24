cmake_minimum_required(VERSION 3.13)

project(events)
file(GLOB SOURCES "*.cpp")

add_executable(events ${SOURCES})