project(data_loader)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_BUILD_TYPE "Debug")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories(include/others)
include_directories(include/features)

include(../cmake/opencv.cmake)
include(../cmake/eigen3.cmake)

set(SRC src/preprocess.cc
        src/tic_toc.cpp)



add_executable(main app/main.cpp ${SRC}) 