cmake_minimum_required(VERSION 2.8)

project(ceres-test)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

include(../cmake/g2o.cmake)
# helloworld
add_executable(ceres_icp_analystic_se3 ceres_self_example/ceres_icp_analystic_se3.cpp)
target_link_libraries(ceres_icp_analystic_se3 ${CERES_LIBRARIES} )

add_executable(ceres_icp_autodiff_q_r3 ceres_self_example/ceres_icp_autodiff_q_r3.cpp)
target_link_libraries(ceres_icp_autodiff_q_r3 ${CERES_LIBRARIES} )