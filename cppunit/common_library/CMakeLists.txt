cmake_minimum_required(VERSION 3.14)

project(common_library)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
include(CTest)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG release-1.12.1)


# CMake 3.14+
FetchContent_MakeAvailable(googletest)

add_library(commonLibrary LibraryCode.cpp)
add_executable(mainApp main.cpp)
target_link_libraries(mainApp commonLibrary)

add_executable(unitTestRunner testRunner.cpp)
target_link_libraries(unitTestRunner commonLibrary gtest_main gmock_main)

enable_testing()
#[[add_test(TestSuiteSample unitTestRunner)]]

add_test(
  NAME unitTestRunner
  COMMAND $<TARGET_FILE:unitTestRunner>
)