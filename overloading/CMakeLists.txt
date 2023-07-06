cmake_minimum_required(VERSION 3.17)
project(overloading)

set(CXX_STANDARD_REQUIRED 17)
add_executable(assign_op_with_ptr assign_op_with_ptr.cpp)
add_executable(assign_op_with_ptr_array assign_op_with_ptr_array.cpp)
add_executable(overload_typecast overload_typecast.cpp)

add_executable(vector_overalod_typecast vector_overalod_typecast.cpp)


