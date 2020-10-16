project(yaml-test)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++11 -o3")

find_package(yaml-cpp REQUIRED)

include_directories(${YAML_CPP_INCLUDE_DIR})

message(STATUS  ${YAML_CPP_INCLUDE_DIR})
message(STATUS  ${YAML_CPP_LIBRARIES})

add_executable(yaml-test yaml-test.cpp)

target_link_libraries(yaml-test ${YAML_CPP_LIBRARIES})