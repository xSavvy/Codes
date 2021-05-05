cmake_minimum_required(VERSION 2.8.11)
project(euroc_tracking)

set(CMAKE_CXX_FLAGS "-std=c++11 -o2")

include_directories("/usr/local/include/eigen3")
include_directories("/usr/include/eigen3")


find_package(OpenCV REQUIRED)

find_package(yaml-cpp REQUIRED)

include_directories(${YAML_CPP_INCLUDE_DIR})
include_directories(
    ${OpenCV_INCLUDE_DIR}
)


link_libraries( yaml-cpp)
link_libraries(

    ${OpenCV_LIBS}
)
find_package(glog REQUIRED)
## 找注意glog 的时候和别的库不一样 就是一个链接
link_libraries(
glog
)
add_executable(EuRoC_test EuRoC_test.cpp param.cc)
