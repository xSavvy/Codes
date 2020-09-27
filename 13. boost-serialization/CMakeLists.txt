project(boost-serialzation-test)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY devel)

# 具体内容可见 https://blog.csdn.net/jinzhu1911/article/details/104940277
# COMPONENTS 的意思就是必须要找到什么包 不然就会报错
find_package(Boost REQUIRED COMPONENTS serialization)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(simple-case-test ./simple-case-test.cpp)
target_link_libraries(simple-case-test ${Boost_LIBRARIES})

add_executable(simple-case-no-invasive ./simple-case-no-invasive.cpp)
target_link_libraries(simple-case-no-invasive ${Boost_LIBRARIES})

add_executable(derived-base-serialization ./derived-base-serialization.cpp)
target_link_libraries(derived-base-serialization ${Boost_LIBRARIES})