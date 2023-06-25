cmake_minimum_required(VERSION 3.13)

project(common_library)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG release-1.12.1)

FetchContent_GetProperties(googletest)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

add_library(commonLibrary LibraryCode.cpp)
add_executable(mainApp main.cpp)
target_link_libraries(mainApp commonLibrary)

add_executable(unitTestRunner testRunner.cpp)
target_link_libraries(unitTestRunner commonLibrary gtest_main gmock_main)
