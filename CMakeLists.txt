cmake_minimum_required(VERSION 3.4)

add_library(iMath Vector.h Matrix.h Vector.cpp Matrix.cpp)
add_executable(test_vector test.cpp)
target_link_libraries(test_vector iMath)
