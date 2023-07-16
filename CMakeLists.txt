cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1    
)
FetchContent_MakeAvailable(googletest)

project(cpp_top_level)
add_subdirectory(templates)
add_subdirectory(interrupts)
add_subdirectory(design_patterns)
add_subdirectory(unittest)
add_subdirectory(oop)
add_subdirectory(overloading)
add_subdirectory(exception_handling)
add_subdirectory(ERULES)
add_subdirectory(memory_management)
add_subdirectory(adv_topics)
add_subdirectory(stl)
add_subdirectory(hackerrank)