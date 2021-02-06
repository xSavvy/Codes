project(HW4)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "-std=c++14")


include(../../../cmake/opencv.cmake)
include(../../../cmake/eigen3.cmake)
add_executable(img_un image_undistort.cpp)