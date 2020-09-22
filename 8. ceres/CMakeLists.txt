cmake_minimum_required(VERSION 2.8)

project(ceres-test)
set(CMAKE_BUILD_TYPE "Debug")
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})


# helloworld
add_executable(basic-test basic-test.cpp)
target_link_libraries(basic-test ${CERES_LIBRARIES})
add_executable(2nd-basic-test 2nd-basic-test.cpp)
target_link_libraries(2nd-basic-test ${CERES_LIBRARIES})
add_executable(3rd-basic-test 3rd-basic-test.cpp)
target_link_libraries(3rd-basic-test ${CERES_LIBRARIES})

add_executable(5th-self-define-evaluate 5th-how-to-write-function-usable-in-ceres.cpp)
target_link_libraries(5th-self-define-evaluate ${CERES_LIBRARIES})

#开始尝试ceres的接口
add_executable(6th-a-value-return-function-for-autodiff 6th-a-value-return-function-for-autodiff.cpp)
target_link_libraries(6th-a-value-return-function-for-autodiff ${CERES_LIBRARIES})