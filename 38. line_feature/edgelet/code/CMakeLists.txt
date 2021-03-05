project(edgelet_tracker)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++14 -o3")
set(CMAKE_BUILD_TYPE "Debug")

include(../../../cmake/opencv.cmake)

add_executable(test_edgelet test_edgelet.cc)