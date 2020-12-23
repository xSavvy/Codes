project(pangolin_test)

find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
add_executable(pangolin_cube pangolin_cube.cpp)
target_link_libraries(pangolin_cube ${Pangolin_LIBRARIES})
add_executable(pangolin_coordinate pangolin_coordinate.cpp)
target_link_libraries(pangolin_coordinate ${Pangolin_LIBRARIES})