# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/build"

# Include any dependencies generated for this target.
include CMakeFiles/test_case.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_case.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_case.dir/flags.make

CMakeFiles/test_case.dir/test_case.cpp.o: CMakeFiles/test_case.dir/flags.make
CMakeFiles/test_case.dir/test_case.cpp.o: ../test_case.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_case.dir/test_case.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_case.dir/test_case.cpp.o -c "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/test_case.cpp"

CMakeFiles/test_case.dir/test_case.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_case.dir/test_case.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/test_case.cpp" > CMakeFiles/test_case.dir/test_case.cpp.i

CMakeFiles/test_case.dir/test_case.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_case.dir/test_case.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/test_case.cpp" -o CMakeFiles/test_case.dir/test_case.cpp.s

CMakeFiles/test_case.dir/VPDetection.cpp.o: CMakeFiles/test_case.dir/flags.make
CMakeFiles/test_case.dir/VPDetection.cpp.o: ../VPDetection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_case.dir/VPDetection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_case.dir/VPDetection.cpp.o -c "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/VPDetection.cpp"

CMakeFiles/test_case.dir/VPDetection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_case.dir/VPDetection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/VPDetection.cpp" > CMakeFiles/test_case.dir/VPDetection.cpp.i

CMakeFiles/test_case.dir/VPDetection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_case.dir/VPDetection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/VPDetection.cpp" -o CMakeFiles/test_case.dir/VPDetection.cpp.s

# Object files for target test_case
test_case_OBJECTS = \
"CMakeFiles/test_case.dir/test_case.cpp.o" \
"CMakeFiles/test_case.dir/VPDetection.cpp.o"

# External object files for target test_case
test_case_EXTERNAL_OBJECTS =

test_case: CMakeFiles/test_case.dir/test_case.cpp.o
test_case: CMakeFiles/test_case.dir/VPDetection.cpp.o
test_case: CMakeFiles/test_case.dir/build.make
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_stitching3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_superres3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_videostab3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_aruco3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_bgsegm3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_bioinspired3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_ccalib3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_cvv3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_dpm3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_face3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_fuzzy3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_hdf3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_img_hash3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_line_descriptor3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_optflow3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_reg3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_rgbd3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_saliency3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_stereo3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_structured_light3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_surface_matching3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_tracking3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_xfeatures2d3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_ximgproc3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_xobjdetect3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_xphoto3.so.3.3.1
test_case: /usr/local/lib/libceres.a
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_shape3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_photo3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_datasets3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_plot3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_text3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_dnn3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_ml3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_video3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_calib3d3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_features2d3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_highgui3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_videoio3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_viz3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_phase_unwrapping3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_flann3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgcodecs3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_objdetect3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_imgproc3.so.3.3.1
test_case: /opt/ros/kinetic/lib/x86_64-linux-gnu/libopencv_core3.so.3.3.1
test_case: /usr/local/lib/libglog.a
test_case: /usr/lib/x86_64-linux-gnu/libgflags.so
test_case: /usr/lib/x86_64-linux-gnu/libspqr.so
test_case: /usr/lib/x86_64-linux-gnu/libtbbmalloc.so
test_case: /usr/lib/x86_64-linux-gnu/libtbb.so
test_case: /usr/lib/x86_64-linux-gnu/libcholmod.so
test_case: /usr/lib/x86_64-linux-gnu/libccolamd.so
test_case: /usr/lib/x86_64-linux-gnu/libcamd.so
test_case: /usr/lib/x86_64-linux-gnu/libcolamd.so
test_case: /usr/lib/x86_64-linux-gnu/libamd.so
test_case: /usr/lib/liblapack.so
test_case: /usr/lib/libf77blas.so
test_case: /usr/lib/libatlas.so
test_case: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
test_case: /usr/lib/x86_64-linux-gnu/librt.so
test_case: /usr/lib/x86_64-linux-gnu/libcxsparse.so
test_case: /usr/lib/x86_64-linux-gnu/libtbbmalloc.so
test_case: /usr/lib/x86_64-linux-gnu/libtbb.so
test_case: /usr/lib/x86_64-linux-gnu/libcholmod.so
test_case: /usr/lib/x86_64-linux-gnu/libccolamd.so
test_case: /usr/lib/x86_64-linux-gnu/libcamd.so
test_case: /usr/lib/x86_64-linux-gnu/libcolamd.so
test_case: /usr/lib/x86_64-linux-gnu/libamd.so
test_case: /usr/lib/liblapack.so
test_case: /usr/lib/libf77blas.so
test_case: /usr/lib/libatlas.so
test_case: /usr/lib/x86_64-linux-gnu/libsuitesparseconfig.so
test_case: /usr/lib/x86_64-linux-gnu/librt.so
test_case: /usr/lib/x86_64-linux-gnu/libcxsparse.so
test_case: CMakeFiles/test_case.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_case"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_case.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_case.dir/build: test_case

.PHONY : CMakeFiles/test_case.dir/build

CMakeFiles/test_case.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_case.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_case.dir/clean

CMakeFiles/test_case.dir/depend:
	cd "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code" "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code" "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/build" "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/build" "/home/lwl/workspace/3rd-test-learning/38. line_feature/vanishing_point/code/build/CMakeFiles/test_case.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/test_case.dir/depend

