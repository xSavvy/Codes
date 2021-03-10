project(line_sim)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_BUILD_TYPE "Debug")

include(../../cmake/opencv.cmake)
include(../../cmake/pangolin.cmake)
include(../../cmake/eigen3.cmake)
include(../../cmake/ceres.cmake)

add_executable(test_sim test_sim.cc)
add_executable(test_angle test_angle.cc)