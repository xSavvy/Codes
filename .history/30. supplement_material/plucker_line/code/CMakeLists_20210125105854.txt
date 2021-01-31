project(line_test)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++11")


include(../../cmake/eigen3.cmake)
include(../../cmake/pangolin.cmake)
include(../../cmake/sophus.cmake)



add_executable(plucker_test plucker_test.cpp)