project(eigen_test)


set(CMAKE_CXX_FLAGS "-std=c++11")
include_directories("/usr/local/include/eigen3")
include_directories("/usr/include/eigen3")
include_directories("/usr/local/include/sophus")

add_executable(eigen_svd eigen_svd.cpp)