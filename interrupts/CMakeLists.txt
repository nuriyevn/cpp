cmake_minimum_required(VERSION 3.1)

project(cpp_interrupts)
add_subdirectory(events)
add_executable(InterruptsWithTimer interrupts_timer.cpp)