project(data_loader_deep_vo)
cmake_minimum_required( VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Debug")


find_package(OpenCV 3.4 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
link_libraries(${OpenCV_LIBS})

include_directories("/usr/local/include/eigen3")
include_directories("/usr/include/eigen3")

include_directories("/usr/local/include/sophus")

add_executable(test_case test_case.cc)