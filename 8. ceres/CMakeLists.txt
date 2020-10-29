cmake_minimum_required(VERSION 2.8)

project(ceres-test)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

include(../cmake/g2o.cmake)
# helloworld
add_executable(local_parameter_test ceres_self_example/local_parameter_test.cpp)
target_link_libraries(local_parameter_test ${CERES_LIBRARIES} )
