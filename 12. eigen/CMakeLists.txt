project(eigen-test)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++11 ")
include_directories("/usr/local/include/eigen3")

add_executable(map_test map_test.cpp)
add_executable(llt_test llt_test.cpp)