project(eigen-test)
cmake_minimum_required(VERSION 3.5)

find_package(Eigen3 3.3.7 REQUIRED)

message(STATUS "aaaaaa" ${EIGEN3_VERSION_STRING})

include_directories("/usr/local/include/eigen3")

add_executable(eigen-test-array-vector eigen-test-array-vector.cpp)
add_executable(eigen_llt eigen_llt.cpp)