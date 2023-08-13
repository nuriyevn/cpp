cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1    
)
FetchContent_MakeAvailable(googletest)

project(cpp_top_level)
add_subdirectory(adv_topics)
add_subdirectory(core_guidelines)
add_subdirectory(design_patterns)
add_subdirectory(exception_handling)
add_subdirectory(expressions)
add_subdirectory(hackerrank)
add_subdirectory(interrupts)
add_subdirectory(linux)
add_subdirectory(memory_management)
add_subdirectory(oop)
add_subdirectory(overloading)
add_subdirectory(stl)
add_subdirectory(templates)
add_subdirectory(unittest)
