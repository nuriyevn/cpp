cmake_minimum_required(VERSION 3.17)

project(basic_guarantee)


include(FetchContent)

FetchContent_Declare(googletest 
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1    
)

FetchContent_MakeAvailable(googletest)

add_executable(BasicGuarantee basic_strong_nothrow_guarantees.cpp)


