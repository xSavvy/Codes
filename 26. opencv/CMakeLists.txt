project(opencv_test)
cmake_minimum_required(VERSION 2.8)
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
link_libraries(${OpenCV_LIBS})


add_executable(basic_io basic_io.cpp)