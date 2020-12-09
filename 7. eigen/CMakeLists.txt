project(eigen-test)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++14")
find_package(Eigen3 3.3.7 REQUIRED)

message(STATUS "aaaaaa" ${EIGEN3_VERSION_STRING})

include_directories("/usr/local/include/eigen3")
include(../cmake/eigen3.cmake)
# include(../cmake/PCL.cmake)
include(../cmake/omp.cmake)

# add_executable(eigen-test-array-vector eigen-test-array-vector.cpp)
# add_executable(eigen_llt eigen_llt.cpp)
# add_executable(eigen_icp eigen_icp.cpp)
# add_executable(omp_test omp_test.cpp)
# add_executable(template_transpose eigen_template_transpose.cpp)
add_executable(ap alignment_problem.cpp)