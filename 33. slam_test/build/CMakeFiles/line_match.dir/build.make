# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/sunny/workspace_private/3rd-test-learning/33. slam_test"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/build"

# Include any dependencies generated for this target.
include CMakeFiles/line_match.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/line_match.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/line_match.dir/flags.make

CMakeFiles/line_match.dir/example/test_line_match.cpp.o: CMakeFiles/line_match.dir/flags.make
CMakeFiles/line_match.dir/example/test_line_match.cpp.o: ../example/test_line_match.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sunny/workspace_private/3rd-test-learning/33. slam_test/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/line_match.dir/example/test_line_match.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/line_match.dir/example/test_line_match.cpp.o -c "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/example/test_line_match.cpp"

CMakeFiles/line_match.dir/example/test_line_match.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/line_match.dir/example/test_line_match.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/example/test_line_match.cpp" > CMakeFiles/line_match.dir/example/test_line_match.cpp.i

CMakeFiles/line_match.dir/example/test_line_match.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/line_match.dir/example/test_line_match.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/example/test_line_match.cpp" -o CMakeFiles/line_match.dir/example/test_line_match.cpp.s

CMakeFiles/line_match.dir/example/test_line_match.cpp.o.requires:

.PHONY : CMakeFiles/line_match.dir/example/test_line_match.cpp.o.requires

CMakeFiles/line_match.dir/example/test_line_match.cpp.o.provides: CMakeFiles/line_match.dir/example/test_line_match.cpp.o.requires
	$(MAKE) -f CMakeFiles/line_match.dir/build.make CMakeFiles/line_match.dir/example/test_line_match.cpp.o.provides.build
.PHONY : CMakeFiles/line_match.dir/example/test_line_match.cpp.o.provides

CMakeFiles/line_match.dir/example/test_line_match.cpp.o.provides.build: CMakeFiles/line_match.dir/example/test_line_match.cpp.o


CMakeFiles/line_match.dir/src/preprocess.cc.o: CMakeFiles/line_match.dir/flags.make
CMakeFiles/line_match.dir/src/preprocess.cc.o: ../src/preprocess.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sunny/workspace_private/3rd-test-learning/33. slam_test/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/line_match.dir/src/preprocess.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/line_match.dir/src/preprocess.cc.o -c "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/src/preprocess.cc"

CMakeFiles/line_match.dir/src/preprocess.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/line_match.dir/src/preprocess.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/src/preprocess.cc" > CMakeFiles/line_match.dir/src/preprocess.cc.i

CMakeFiles/line_match.dir/src/preprocess.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/line_match.dir/src/preprocess.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/src/preprocess.cc" -o CMakeFiles/line_match.dir/src/preprocess.cc.s

CMakeFiles/line_match.dir/src/preprocess.cc.o.requires:

.PHONY : CMakeFiles/line_match.dir/src/preprocess.cc.o.requires

CMakeFiles/line_match.dir/src/preprocess.cc.o.provides: CMakeFiles/line_match.dir/src/preprocess.cc.o.requires
	$(MAKE) -f CMakeFiles/line_match.dir/build.make CMakeFiles/line_match.dir/src/preprocess.cc.o.provides.build
.PHONY : CMakeFiles/line_match.dir/src/preprocess.cc.o.provides

CMakeFiles/line_match.dir/src/preprocess.cc.o.provides.build: CMakeFiles/line_match.dir/src/preprocess.cc.o


CMakeFiles/line_match.dir/src/tic_toc.cc.o: CMakeFiles/line_match.dir/flags.make
CMakeFiles/line_match.dir/src/tic_toc.cc.o: ../src/tic_toc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sunny/workspace_private/3rd-test-learning/33. slam_test/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/line_match.dir/src/tic_toc.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/line_match.dir/src/tic_toc.cc.o -c "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/src/tic_toc.cc"

CMakeFiles/line_match.dir/src/tic_toc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/line_match.dir/src/tic_toc.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/src/tic_toc.cc" > CMakeFiles/line_match.dir/src/tic_toc.cc.i

CMakeFiles/line_match.dir/src/tic_toc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/line_match.dir/src/tic_toc.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/src/tic_toc.cc" -o CMakeFiles/line_match.dir/src/tic_toc.cc.s

CMakeFiles/line_match.dir/src/tic_toc.cc.o.requires:

.PHONY : CMakeFiles/line_match.dir/src/tic_toc.cc.o.requires

CMakeFiles/line_match.dir/src/tic_toc.cc.o.provides: CMakeFiles/line_match.dir/src/tic_toc.cc.o.requires
	$(MAKE) -f CMakeFiles/line_match.dir/build.make CMakeFiles/line_match.dir/src/tic_toc.cc.o.provides.build
.PHONY : CMakeFiles/line_match.dir/src/tic_toc.cc.o.provides

CMakeFiles/line_match.dir/src/tic_toc.cc.o.provides.build: CMakeFiles/line_match.dir/src/tic_toc.cc.o


CMakeFiles/line_match.dir/src/line_extractor.cc.o: CMakeFiles/line_match.dir/flags.make
CMakeFiles/line_match.dir/src/line_extractor.cc.o: ../src/line_extractor.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/sunny/workspace_private/3rd-test-learning/33. slam_test/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/line_match.dir/src/line_extractor.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/line_match.dir/src/line_extractor.cc.o -c "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/src/line_extractor.cc"

CMakeFiles/line_match.dir/src/line_extractor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/line_match.dir/src/line_extractor.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/src/line_extractor.cc" > CMakeFiles/line_match.dir/src/line_extractor.cc.i

CMakeFiles/line_match.dir/src/line_extractor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/line_match.dir/src/line_extractor.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/src/line_extractor.cc" -o CMakeFiles/line_match.dir/src/line_extractor.cc.s

CMakeFiles/line_match.dir/src/line_extractor.cc.o.requires:

.PHONY : CMakeFiles/line_match.dir/src/line_extractor.cc.o.requires

CMakeFiles/line_match.dir/src/line_extractor.cc.o.provides: CMakeFiles/line_match.dir/src/line_extractor.cc.o.requires
	$(MAKE) -f CMakeFiles/line_match.dir/build.make CMakeFiles/line_match.dir/src/line_extractor.cc.o.provides.build
.PHONY : CMakeFiles/line_match.dir/src/line_extractor.cc.o.provides

CMakeFiles/line_match.dir/src/line_extractor.cc.o.provides.build: CMakeFiles/line_match.dir/src/line_extractor.cc.o


# Object files for target line_match
line_match_OBJECTS = \
"CMakeFiles/line_match.dir/example/test_line_match.cpp.o" \
"CMakeFiles/line_match.dir/src/preprocess.cc.o" \
"CMakeFiles/line_match.dir/src/tic_toc.cc.o" \
"CMakeFiles/line_match.dir/src/line_extractor.cc.o"

# External object files for target line_match
line_match_EXTERNAL_OBJECTS =

../example/_output/line_match: CMakeFiles/line_match.dir/example/test_line_match.cpp.o
../example/_output/line_match: CMakeFiles/line_match.dir/src/preprocess.cc.o
../example/_output/line_match: CMakeFiles/line_match.dir/src/tic_toc.cc.o
../example/_output/line_match: CMakeFiles/line_match.dir/src/line_extractor.cc.o
../example/_output/line_match: CMakeFiles/line_match.dir/build.make
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_stitching.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_superres.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_videostab.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_aruco.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_bgsegm.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_bioinspired.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_ccalib.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_dpm.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_face.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_freetype.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_fuzzy.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_hdf.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_img_hash.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_line_descriptor.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_optflow.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_reg.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_rgbd.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_saliency.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_sfm.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_stereo.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_structured_light.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_surface_matching.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_tracking.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_xfeatures2d.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_ximgproc.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_xobjdetect.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_xphoto.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_photo.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_shape.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_calib3d.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_viz.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_phase_unwrapping.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_video.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_datasets.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_plot.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_text.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_dnn.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_features2d.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_flann.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_highgui.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_ml.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_videoio.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_imgcodecs.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_objdetect.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_imgproc.so.3.3.1
../example/_output/line_match: /home/sunny/3rdparty/opencv3.3.1/lib/libopencv_core.so.3.3.1
../example/_output/line_match: CMakeFiles/line_match.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/sunny/workspace_private/3rd-test-learning/33. slam_test/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../example/_output/line_match"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/line_match.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/line_match.dir/build: ../example/_output/line_match

.PHONY : CMakeFiles/line_match.dir/build

CMakeFiles/line_match.dir/requires: CMakeFiles/line_match.dir/example/test_line_match.cpp.o.requires
CMakeFiles/line_match.dir/requires: CMakeFiles/line_match.dir/src/preprocess.cc.o.requires
CMakeFiles/line_match.dir/requires: CMakeFiles/line_match.dir/src/tic_toc.cc.o.requires
CMakeFiles/line_match.dir/requires: CMakeFiles/line_match.dir/src/line_extractor.cc.o.requires

.PHONY : CMakeFiles/line_match.dir/requires

CMakeFiles/line_match.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/line_match.dir/cmake_clean.cmake
.PHONY : CMakeFiles/line_match.dir/clean

CMakeFiles/line_match.dir/depend:
	cd "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/sunny/workspace_private/3rd-test-learning/33. slam_test" "/home/sunny/workspace_private/3rd-test-learning/33. slam_test" "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/build" "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/build" "/home/sunny/workspace_private/3rd-test-learning/33. slam_test/build/CMakeFiles/line_match.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/line_match.dir/depend
