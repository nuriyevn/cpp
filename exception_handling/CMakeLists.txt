cmake_minimum_required(VERSION 3.17)

project(basic_guarantee)


include(FetchContent)

FetchContent_Declare(googletest 
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1    
)

FetchContent_MakeAvailable(googletest)

add_library(DateLibrary date.cpp)

add_executable(BasicGuarantee basic_guarantee.cpp)
target_link_libraries(BasicGuarantee DateLibrary)
set(CMAKE_CXX_STANDARD 14)
#[[set(CMAKE_CXX_FLAGS "-fno-elide-constructors")]]
add_executable(except_throw except.throw.cpp)


