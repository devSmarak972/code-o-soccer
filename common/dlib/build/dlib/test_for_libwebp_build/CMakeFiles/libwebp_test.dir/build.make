# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/chinmay/.local/bin/cmake

# The command to remove a file.
RM = /home/chinmay/.local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/dlib/cmake_utils/test_for_libwebp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/build/dlib/test_for_libwebp_build

# Include any dependencies generated for this target.
include CMakeFiles/libwebp_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libwebp_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libwebp_test.dir/flags.make

CMakeFiles/libwebp_test.dir/libwebp_test.cpp.o: CMakeFiles/libwebp_test.dir/flags.make
CMakeFiles/libwebp_test.dir/libwebp_test.cpp.o: /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/dlib/cmake_utils/test_for_libwebp/libwebp_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/build/dlib/test_for_libwebp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libwebp_test.dir/libwebp_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libwebp_test.dir/libwebp_test.cpp.o -c /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/dlib/cmake_utils/test_for_libwebp/libwebp_test.cpp

CMakeFiles/libwebp_test.dir/libwebp_test.cpp.i: cmake_force
	@echo "Preprocessing CXX source to CMakeFiles/libwebp_test.dir/libwebp_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/dlib/cmake_utils/test_for_libwebp/libwebp_test.cpp > CMakeFiles/libwebp_test.dir/libwebp_test.cpp.i

CMakeFiles/libwebp_test.dir/libwebp_test.cpp.s: cmake_force
	@echo "Compiling CXX source to assembly CMakeFiles/libwebp_test.dir/libwebp_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/dlib/cmake_utils/test_for_libwebp/libwebp_test.cpp -o CMakeFiles/libwebp_test.dir/libwebp_test.cpp.s

# Object files for target libwebp_test
libwebp_test_OBJECTS = \
"CMakeFiles/libwebp_test.dir/libwebp_test.cpp.o"

# External object files for target libwebp_test
libwebp_test_EXTERNAL_OBJECTS =

libwebp_test: CMakeFiles/libwebp_test.dir/libwebp_test.cpp.o
libwebp_test: CMakeFiles/libwebp_test.dir/build.make
libwebp_test: CMakeFiles/libwebp_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/build/dlib/test_for_libwebp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable libwebp_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libwebp_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libwebp_test.dir/build: libwebp_test

.PHONY : CMakeFiles/libwebp_test.dir/build

CMakeFiles/libwebp_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libwebp_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libwebp_test.dir/clean

CMakeFiles/libwebp_test.dir/depend:
	cd /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/build/dlib/test_for_libwebp_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/dlib/cmake_utils/test_for_libwebp /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/dlib/cmake_utils/test_for_libwebp /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/build/dlib/test_for_libwebp_build /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/build/dlib/test_for_libwebp_build /home/chinmay/KRSSG_ALL/kgpkubs-southkorea/common/dlib/build/dlib/test_for_libwebp_build/CMakeFiles/libwebp_test.dir/DependInfo.cmake
.PHONY : CMakeFiles/libwebp_test.dir/depend
