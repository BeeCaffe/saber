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
include CMakeFiles/saber.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/saber.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/saber.dir/flags.make

CMakeFiles/saber.dir/saber/log.cc.o: CMakeFiles/saber.dir/flags.make
CMakeFiles/saber.dir/saber/log.cc.o: ../saber/log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/saber.dir/saber/log.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber.dir/saber/log.cc.o -c /home/beecaffe/src/saber/saber/log.cc

CMakeFiles/saber.dir/saber/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber.dir/saber/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/log.cc > CMakeFiles/saber.dir/saber/log.cc.i

CMakeFiles/saber.dir/saber/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber.dir/saber/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/log.cc -o CMakeFiles/saber.dir/saber/log.cc.s

CMakeFiles/saber.dir/saber/log.cc.o.requires:

.PHONY : CMakeFiles/saber.dir/saber/log.cc.o.requires

CMakeFiles/saber.dir/saber/log.cc.o.provides: CMakeFiles/saber.dir/saber/log.cc.o.requires
	$(MAKE) -f CMakeFiles/saber.dir/build.make CMakeFiles/saber.dir/saber/log.cc.o.provides.build
.PHONY : CMakeFiles/saber.dir/saber/log.cc.o.provides

CMakeFiles/saber.dir/saber/log.cc.o.provides.build: CMakeFiles/saber.dir/saber/log.cc.o


CMakeFiles/saber.dir/saber/utils.cc.o: CMakeFiles/saber.dir/flags.make
CMakeFiles/saber.dir/saber/utils.cc.o: ../saber/utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/saber.dir/saber/utils.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber.dir/saber/utils.cc.o -c /home/beecaffe/src/saber/saber/utils.cc

CMakeFiles/saber.dir/saber/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber.dir/saber/utils.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/utils.cc > CMakeFiles/saber.dir/saber/utils.cc.i

CMakeFiles/saber.dir/saber/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber.dir/saber/utils.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/utils.cc -o CMakeFiles/saber.dir/saber/utils.cc.s

CMakeFiles/saber.dir/saber/utils.cc.o.requires:

.PHONY : CMakeFiles/saber.dir/saber/utils.cc.o.requires

CMakeFiles/saber.dir/saber/utils.cc.o.provides: CMakeFiles/saber.dir/saber/utils.cc.o.requires
	$(MAKE) -f CMakeFiles/saber.dir/build.make CMakeFiles/saber.dir/saber/utils.cc.o.provides.build
.PHONY : CMakeFiles/saber.dir/saber/utils.cc.o.provides

CMakeFiles/saber.dir/saber/utils.cc.o.provides.build: CMakeFiles/saber.dir/saber/utils.cc.o


CMakeFiles/saber.dir/saber/json/json.cc.o: CMakeFiles/saber.dir/flags.make
CMakeFiles/saber.dir/saber/json/json.cc.o: ../saber/json/json.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/saber.dir/saber/json/json.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber.dir/saber/json/json.cc.o -c /home/beecaffe/src/saber/saber/json/json.cc

CMakeFiles/saber.dir/saber/json/json.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber.dir/saber/json/json.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/json/json.cc > CMakeFiles/saber.dir/saber/json/json.cc.i

CMakeFiles/saber.dir/saber/json/json.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber.dir/saber/json/json.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/json/json.cc -o CMakeFiles/saber.dir/saber/json/json.cc.s

CMakeFiles/saber.dir/saber/json/json.cc.o.requires:

.PHONY : CMakeFiles/saber.dir/saber/json/json.cc.o.requires

CMakeFiles/saber.dir/saber/json/json.cc.o.provides: CMakeFiles/saber.dir/saber/json/json.cc.o.requires
	$(MAKE) -f CMakeFiles/saber.dir/build.make CMakeFiles/saber.dir/saber/json/json.cc.o.provides.build
.PHONY : CMakeFiles/saber.dir/saber/json/json.cc.o.provides

CMakeFiles/saber.dir/saber/json/json.cc.o.provides.build: CMakeFiles/saber.dir/saber/json/json.cc.o


# Object files for target saber
saber_OBJECTS = \
"CMakeFiles/saber.dir/saber/log.cc.o" \
"CMakeFiles/saber.dir/saber/utils.cc.o" \
"CMakeFiles/saber.dir/saber/json/json.cc.o"

# External object files for target saber
saber_EXTERNAL_OBJECTS =

../lib/libsaber.so: CMakeFiles/saber.dir/saber/log.cc.o
../lib/libsaber.so: CMakeFiles/saber.dir/saber/utils.cc.o
../lib/libsaber.so: CMakeFiles/saber.dir/saber/json/json.cc.o
../lib/libsaber.so: CMakeFiles/saber.dir/build.make
../lib/libsaber.so: CMakeFiles/saber.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library ../lib/libsaber.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/saber.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/saber.dir/build: ../lib/libsaber.so

.PHONY : CMakeFiles/saber.dir/build

CMakeFiles/saber.dir/requires: CMakeFiles/saber.dir/saber/log.cc.o.requires
CMakeFiles/saber.dir/requires: CMakeFiles/saber.dir/saber/utils.cc.o.requires
CMakeFiles/saber.dir/requires: CMakeFiles/saber.dir/saber/json/json.cc.o.requires

.PHONY : CMakeFiles/saber.dir/requires

CMakeFiles/saber.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/saber.dir/cmake_clean.cmake
.PHONY : CMakeFiles/saber.dir/clean

CMakeFiles/saber.dir/depend:
	cd /home/beecaffe/src/saber/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/beecaffe/src/saber /home/beecaffe/src/saber /home/beecaffe/src/saber/build /home/beecaffe/src/saber/build /home/beecaffe/src/saber/build/CMakeFiles/saber.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/saber.dir/depend

