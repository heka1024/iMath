cmake_minimum_required(VERSION 3.4)

add_library(Vector Vector.h Vector.cpp)
add_executable(test_vector test.cpp)
target_link_libraries(test_vector Vector)
