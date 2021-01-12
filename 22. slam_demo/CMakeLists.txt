cmake_minimum_required(VERSION 3.5)
project(slam_demo)
set(CMAKE_BUILD_TYPE "Debug")


include(../cmake/eigen3.cmake)


add_executable(environment_test environment_test.cpp)
add_executable(PnP_test PnP.cpp)