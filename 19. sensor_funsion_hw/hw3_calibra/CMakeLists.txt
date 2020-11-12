project(hw3)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11 -o3")

include(../../cmake/ceres.cmake)
include(../../cmake/omp.cmake)
include(../../cmake/eigen3.cmake)

add_executable(calibra_accel hw_3_2_accel.cpp)
add_executable(calibra_gyro hw_3_2_gyro.cpp)