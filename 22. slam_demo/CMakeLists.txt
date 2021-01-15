cmake_minimum_required(VERSION 3.5)
project(slam_demo)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-std=c++11 ")

include(../cmake/eigen3.cmake)
include(../cmake/pangolin.cmake)
include(../cmake/opencv.cmake)
include()

add_executable(main_test main_test.cpp)
