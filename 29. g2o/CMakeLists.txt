project(g2o_test)
cmake_minimum_required( VERSION 3.5)


find_package(G2O REQUIRED)
IF(G2O_FOUND)
    include_directories(${G2O_INCLUDE_DIR})
    message("G2O lib is found:"${G2O_INCLUDE_DIR})
ENDIF(G2O_FOUND)

find_package(Eigen3 REQUIRED)
find_package(CSparse REQUIRED)
find_package(Cholmod REQUIRED)
include_directories(${CSPARSE_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${CHOLMOD_INCLUDE_DIR})

SET(G2O_LIBS g2o_cli g2o_ext_freeglut_minimal g2o_simulator 
g2o_solver_slam2d_linear g2o_types_icp g2o_types_slam2d g2o_core 
g2o_interface g2o_solver_csparse g2o_solver_structure_only 
g2o_types_sba g2o_types_slam3d g2o_csparse_extension 
g2o_opengl_helper g2o_solver_dense g2o_stuff g2o_types_sclam2d 
g2o_parser g2o_solver_pcg g2o_types_data g2o_types_sim3 cxsparse )

add_executable(g2o_basic g2o_basic_test.cpp)
target_link_libraries(g2o_basic G2O_LIBS)