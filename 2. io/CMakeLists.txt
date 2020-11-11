project(io_test)
cmake_minimum_required( VERSION 3.5)
set(CMAKE_CXX_FLAGS "-std=c++14 -o3")
set(CMAKE_BUILD_TYPE "Debug")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  rosbag
)

include(../cmake/omp.cmake)

include_directories(.
                    ${catkin_INCLUDE_DIRS})
# csv 读取
# add_executable(read_csv csv/imu_csv_to_rosbag.cpp)

# csv 到 rosbag
add_executable(csv_to_rosbag "synthesis/csv_to_rosbag.cpp")
target_link_libraries(csv_to_rosbag PRIVATE ${catkin_LIBRARIES})
