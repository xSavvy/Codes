project(tracker)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "-std=c++14 -o3")
set(CMAKE_BUILD_TYPE  "Debug")

include_directories(.)

include(../../../cmake/omp.cmake)
include(../../../cmake/opencv.cmake)
include(../../../cmake/eigen3.cmake)
include(../../../cmake/sophus.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(test_common  test_common.cpp)
add_executable(test_case test_case.cpp)