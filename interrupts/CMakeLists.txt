cmake_minimum_required(VERSION 3.1)

#[[This is a bracket comment.
interrupts, events, async, callbacks, timers, datetime, system logs
It runs until the close bracket.]]

project(cpp_interrupts)
add_subdirectory(events)
add_executable(InterruptsWithTimer interrupts_timer.cpp)
add_executable(async async.cpp)