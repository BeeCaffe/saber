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
CMAKE_SOURCE_DIR = /home/beecaffe/src/saber

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/beecaffe/src/saber/build

# Include any dependencies generated for this target.
include CMakeFiles/log_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/log_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/log_test.dir/flags.make

CMakeFiles/log_test.dir/tests/log_test.cc.o: CMakeFiles/log_test.dir/flags.make
CMakeFiles/log_test.dir/tests/log_test.cc.o: ../tests/log_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/log_test.dir/tests/log_test.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/log_test.dir/tests/log_test.cc.o -c /home/beecaffe/src/saber/tests/log_test.cc

CMakeFiles/log_test.dir/tests/log_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_test.dir/tests/log_test.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/tests/log_test.cc > CMakeFiles/log_test.dir/tests/log_test.cc.i

CMakeFiles/log_test.dir/tests/log_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_test.dir/tests/log_test.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/tests/log_test.cc -o CMakeFiles/log_test.dir/tests/log_test.cc.s

CMakeFiles/log_test.dir/tests/log_test.cc.o.requires:

.PHONY : CMakeFiles/log_test.dir/tests/log_test.cc.o.requires

CMakeFiles/log_test.dir/tests/log_test.cc.o.provides: CMakeFiles/log_test.dir/tests/log_test.cc.o.requires
	$(MAKE) -f CMakeFiles/log_test.dir/build.make CMakeFiles/log_test.dir/tests/log_test.cc.o.provides.build
.PHONY : CMakeFiles/log_test.dir/tests/log_test.cc.o.provides

CMakeFiles/log_test.dir/tests/log_test.cc.o.provides.build: CMakeFiles/log_test.dir/tests/log_test.cc.o


# Object files for target log_test
log_test_OBJECTS = \
"CMakeFiles/log_test.dir/tests/log_test.cc.o"

# External object files for target log_test
log_test_EXTERNAL_OBJECTS =

../bin/log_test: CMakeFiles/log_test.dir/tests/log_test.cc.o
../bin/log_test: CMakeFiles/log_test.dir/build.make
../bin/log_test: ../lib/libsaber.so
../bin/log_test: CMakeFiles/log_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/log_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/log_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/log_test.dir/build: ../bin/log_test

.PHONY : CMakeFiles/log_test.dir/build

CMakeFiles/log_test.dir/requires: CMakeFiles/log_test.dir/tests/log_test.cc.o.requires

.PHONY : CMakeFiles/log_test.dir/requires

CMakeFiles/log_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/log_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/log_test.dir/clean

CMakeFiles/log_test.dir/depend:
	cd /home/beecaffe/src/saber/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/beecaffe/src/saber /home/beecaffe/src/saber /home/beecaffe/src/saber/build /home/beecaffe/src/saber/build /home/beecaffe/src/saber/build/CMakeFiles/log_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/log_test.dir/depend

