project(cpptest)

set(CMAKE_CXX_FLAGS "-std=c++11 -o3")

add_executable(macro_test macro_test.cpp)
add_executable(pure_virtual_mf_inherit pure_virtual_mf_inherit.cpp)