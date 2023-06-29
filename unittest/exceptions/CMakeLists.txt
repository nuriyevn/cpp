cmake_minimum_required(VERSION 3.17)

project(unittest_exceptions)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG release-1.12.1)

FetchContent_MakeAvailable(googletest)

add_library(commonLibary LibraryCode.cpp)
add_executable(exceptionTestRunner testRunner.cpp)
target_link_libraries(exceptionTestRunner commonLibary gtest_main gmock_main)