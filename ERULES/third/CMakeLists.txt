cmake_minimum_required(VERSION 3.17)
project(use_const_whenever_possible_obsolete)
add_executable(ReturnConstString return_const_string.cpp)
add_executable(ReturnConstContainer return_const_container.cpp)
add_executable(ReturnConstObject return_const_object.cpp)



#[[
Benefits of using "const" with scalar type? (e.g. "const double" or "const int")
When returning by value the constant has no effect as it cannot be enforced anyway. Some compilers issue a warning.
However it DOES make sense to return a pointer/reference to constant data.
When passing an argument into a function it is preferable 
(safer, allows for compiler optimizations) to pass it as a constant unless you absolutely need to change the data.
]]