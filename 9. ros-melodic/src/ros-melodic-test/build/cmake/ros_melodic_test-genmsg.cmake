# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "ros_melodic_test: 1 messages, 0 services")

set(MSG_I_FLAGS "-Iros_melodic_test:/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(ros_melodic_test_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg" NAME_WE)
add_custom_target(_ros_melodic_test_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros_melodic_test" "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg" "geometry_msgs/Pose:geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(ros_melodic_test
  "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_melodic_test
)

### Generating Services

### Generating Module File
_generate_module_cpp(ros_melodic_test
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_melodic_test
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(ros_melodic_test_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(ros_melodic_test_generate_messages ros_melodic_test_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg" NAME_WE)
add_dependencies(ros_melodic_test_generate_messages_cpp _ros_melodic_test_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros_melodic_test_gencpp)
add_dependencies(ros_melodic_test_gencpp ros_melodic_test_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_melodic_test_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(ros_melodic_test
  "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_melodic_test
)

### Generating Services

### Generating Module File
_generate_module_eus(ros_melodic_test
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_melodic_test
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(ros_melodic_test_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(ros_melodic_test_generate_messages ros_melodic_test_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg" NAME_WE)
add_dependencies(ros_melodic_test_generate_messages_eus _ros_melodic_test_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros_melodic_test_geneus)
add_dependencies(ros_melodic_test_geneus ros_melodic_test_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_melodic_test_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(ros_melodic_test
  "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_melodic_test
)

### Generating Services

### Generating Module File
_generate_module_lisp(ros_melodic_test
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_melodic_test
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(ros_melodic_test_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(ros_melodic_test_generate_messages ros_melodic_test_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg" NAME_WE)
add_dependencies(ros_melodic_test_generate_messages_lisp _ros_melodic_test_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros_melodic_test_genlisp)
add_dependencies(ros_melodic_test_genlisp ros_melodic_test_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_melodic_test_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(ros_melodic_test
  "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_melodic_test
)

### Generating Services

### Generating Module File
_generate_module_nodejs(ros_melodic_test
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_melodic_test
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(ros_melodic_test_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(ros_melodic_test_generate_messages ros_melodic_test_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg" NAME_WE)
add_dependencies(ros_melodic_test_generate_messages_nodejs _ros_melodic_test_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros_melodic_test_gennodejs)
add_dependencies(ros_melodic_test_gennodejs ros_melodic_test_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_melodic_test_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(ros_melodic_test
  "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_melodic_test
)

### Generating Services

### Generating Module File
_generate_module_py(ros_melodic_test
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_melodic_test
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(ros_melodic_test_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(ros_melodic_test_generate_messages ros_melodic_test_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sunny/workspace_private/3rd-test-learning/9. ros-melodic/src/ros-melodic-test/msg/VisualOdometryMsg.msg" NAME_WE)
add_dependencies(ros_melodic_test_generate_messages_py _ros_melodic_test_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros_melodic_test_genpy)
add_dependencies(ros_melodic_test_genpy ros_melodic_test_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_melodic_test_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_melodic_test)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_melodic_test
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(ros_melodic_test_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(ros_melodic_test_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_melodic_test)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_melodic_test
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(ros_melodic_test_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(ros_melodic_test_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_melodic_test)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_melodic_test
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(ros_melodic_test_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(ros_melodic_test_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_melodic_test)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_melodic_test
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(ros_melodic_test_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(ros_melodic_test_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_melodic_test)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_melodic_test\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_melodic_test
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(ros_melodic_test_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(ros_melodic_test_generate_messages_py std_msgs_generate_messages_py)
endif()
