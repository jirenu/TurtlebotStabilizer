# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/servicerobot2/catkin_ws2/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/servicerobot2/catkin_ws2/build

# Utility rule file for copy_phidget21_plain.

# Include the progress variables for this target.
include libphidgets/CMakeFiles/copy_phidget21_plain.dir/progress.make

libphidgets/CMakeFiles/copy_phidget21_plain:
	cd /home/servicerobot2/catkin_ws2/build/libphidgets && cmake -E copy /home/servicerobot2/catkin_ws2/src/libphidgets/lib/libphidget21.so.0 /home/servicerobot2/catkin_ws2/src/libphidgets/lib/libphidget21.so

copy_phidget21_plain: libphidgets/CMakeFiles/copy_phidget21_plain
copy_phidget21_plain: libphidgets/CMakeFiles/copy_phidget21_plain.dir/build.make
.PHONY : copy_phidget21_plain

# Rule to build all files generated by this target.
libphidgets/CMakeFiles/copy_phidget21_plain.dir/build: copy_phidget21_plain
.PHONY : libphidgets/CMakeFiles/copy_phidget21_plain.dir/build

libphidgets/CMakeFiles/copy_phidget21_plain.dir/clean:
	cd /home/servicerobot2/catkin_ws2/build/libphidgets && $(CMAKE_COMMAND) -P CMakeFiles/copy_phidget21_plain.dir/cmake_clean.cmake
.PHONY : libphidgets/CMakeFiles/copy_phidget21_plain.dir/clean

libphidgets/CMakeFiles/copy_phidget21_plain.dir/depend:
	cd /home/servicerobot2/catkin_ws2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/servicerobot2/catkin_ws2/src /home/servicerobot2/catkin_ws2/src/libphidgets /home/servicerobot2/catkin_ws2/build /home/servicerobot2/catkin_ws2/build/libphidgets /home/servicerobot2/catkin_ws2/build/libphidgets/CMakeFiles/copy_phidget21_plain.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libphidgets/CMakeFiles/copy_phidget21_plain.dir/depend

