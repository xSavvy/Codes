cmake_minimum_required(VERSION 3.5)
project(hw4_filter)
set(CMAKE_CXX_FLAGS "-std=c++14 -o3")
<<<<<<< HEAD
set(CMAKE_BUILD_TYPE "Debug")
=======
>>>>>>> dea03895de9003b39f4d3244d5b32fe33c925837
include(../../cmake/opencv.cmake)
include(../../cmake/eigen3.cmake)
include(../../cmake/sophus.cmake)
include(../../cmake/ceres.cmake)
include(../../cmake/g2o.cmake)
include(../../cmake/omp.cmake)
<<<<<<< HEAD


add_executable(ekf_test ekf_test.cpp
                        ekf.cpp
                        ImuTypes.cc
                        common.cpp)
=======
add_executable(ekf_test ekf_test.cpp)
>>>>>>> dea03895de9003b39f4d3244d5b32fe33c925837
