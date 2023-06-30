cmake_minimum_required(VERSION 3.17)

project(homeacc)
set(CMAKE_CXX_STANDARD 14)
if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MT> #--|
    )
endif()

FetchContent_MakeAvailable(googletest)

add_library(Logger  logger.cpp)
add_library(HomeAccountantLibary  homeacc.cpp)

add_executable(TestHomeAccount test_homeacc.cpp homeacc.cpp )
target_link_libraries(TestHomeAccount HomeAccountantLibary Logger gtest_main gmock_main) 