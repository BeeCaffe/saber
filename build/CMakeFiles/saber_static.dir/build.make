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
include CMakeFiles/saber_static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/saber_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/saber_static.dir/flags.make

CMakeFiles/saber_static.dir/saber/log.cc.o: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/log.cc.o: ../saber/log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/saber_static.dir/saber/log.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber_static.dir/saber/log.cc.o -c /home/beecaffe/src/saber/saber/log.cc

CMakeFiles/saber_static.dir/saber/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/log.cc > CMakeFiles/saber_static.dir/saber/log.cc.i

CMakeFiles/saber_static.dir/saber/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/log.cc -o CMakeFiles/saber_static.dir/saber/log.cc.s

CMakeFiles/saber_static.dir/saber/log.cc.o.requires:

.PHONY : CMakeFiles/saber_static.dir/saber/log.cc.o.requires

CMakeFiles/saber_static.dir/saber/log.cc.o.provides: CMakeFiles/saber_static.dir/saber/log.cc.o.requires
	$(MAKE) -f CMakeFiles/saber_static.dir/build.make CMakeFiles/saber_static.dir/saber/log.cc.o.provides.build
.PHONY : CMakeFiles/saber_static.dir/saber/log.cc.o.provides

CMakeFiles/saber_static.dir/saber/log.cc.o.provides.build: CMakeFiles/saber_static.dir/saber/log.cc.o


CMakeFiles/saber_static.dir/saber/utils.cc.o: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/utils.cc.o: ../saber/utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/saber_static.dir/saber/utils.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber_static.dir/saber/utils.cc.o -c /home/beecaffe/src/saber/saber/utils.cc

CMakeFiles/saber_static.dir/saber/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/utils.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/utils.cc > CMakeFiles/saber_static.dir/saber/utils.cc.i

CMakeFiles/saber_static.dir/saber/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/utils.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/utils.cc -o CMakeFiles/saber_static.dir/saber/utils.cc.s

CMakeFiles/saber_static.dir/saber/utils.cc.o.requires:

.PHONY : CMakeFiles/saber_static.dir/saber/utils.cc.o.requires

CMakeFiles/saber_static.dir/saber/utils.cc.o.provides: CMakeFiles/saber_static.dir/saber/utils.cc.o.requires
	$(MAKE) -f CMakeFiles/saber_static.dir/build.make CMakeFiles/saber_static.dir/saber/utils.cc.o.provides.build
.PHONY : CMakeFiles/saber_static.dir/saber/utils.cc.o.provides

CMakeFiles/saber_static.dir/saber/utils.cc.o.provides.build: CMakeFiles/saber_static.dir/saber/utils.cc.o


CMakeFiles/saber_static.dir/saber/json/json.cc.o: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/json/json.cc.o: ../saber/json/json.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/saber_static.dir/saber/json/json.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber_static.dir/saber/json/json.cc.o -c /home/beecaffe/src/saber/saber/json/json.cc

CMakeFiles/saber_static.dir/saber/json/json.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/json/json.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/json/json.cc > CMakeFiles/saber_static.dir/saber/json/json.cc.i

CMakeFiles/saber_static.dir/saber/json/json.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/json/json.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/json/json.cc -o CMakeFiles/saber_static.dir/saber/json/json.cc.s

CMakeFiles/saber_static.dir/saber/json/json.cc.o.requires:

.PHONY : CMakeFiles/saber_static.dir/saber/json/json.cc.o.requires

CMakeFiles/saber_static.dir/saber/json/json.cc.o.provides: CMakeFiles/saber_static.dir/saber/json/json.cc.o.requires
	$(MAKE) -f CMakeFiles/saber_static.dir/build.make CMakeFiles/saber_static.dir/saber/json/json.cc.o.provides.build
.PHONY : CMakeFiles/saber_static.dir/saber/json/json.cc.o.provides

CMakeFiles/saber_static.dir/saber/json/json.cc.o.provides.build: CMakeFiles/saber_static.dir/saber/json/json.cc.o


CMakeFiles/saber_static.dir/saber/config.cc.o: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/config.cc.o: ../saber/config.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/saber_static.dir/saber/config.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber_static.dir/saber/config.cc.o -c /home/beecaffe/src/saber/saber/config.cc

CMakeFiles/saber_static.dir/saber/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/config.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/config.cc > CMakeFiles/saber_static.dir/saber/config.cc.i

CMakeFiles/saber_static.dir/saber/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/config.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/config.cc -o CMakeFiles/saber_static.dir/saber/config.cc.s

CMakeFiles/saber_static.dir/saber/config.cc.o.requires:

.PHONY : CMakeFiles/saber_static.dir/saber/config.cc.o.requires

CMakeFiles/saber_static.dir/saber/config.cc.o.provides: CMakeFiles/saber_static.dir/saber/config.cc.o.requires
	$(MAKE) -f CMakeFiles/saber_static.dir/build.make CMakeFiles/saber_static.dir/saber/config.cc.o.provides.build
.PHONY : CMakeFiles/saber_static.dir/saber/config.cc.o.provides

CMakeFiles/saber_static.dir/saber/config.cc.o.provides.build: CMakeFiles/saber_static.dir/saber/config.cc.o


CMakeFiles/saber_static.dir/saber/thread.cc.o: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/thread.cc.o: ../saber/thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/saber_static.dir/saber/thread.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber_static.dir/saber/thread.cc.o -c /home/beecaffe/src/saber/saber/thread.cc

CMakeFiles/saber_static.dir/saber/thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/thread.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/thread.cc > CMakeFiles/saber_static.dir/saber/thread.cc.i

CMakeFiles/saber_static.dir/saber/thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/thread.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/thread.cc -o CMakeFiles/saber_static.dir/saber/thread.cc.s

CMakeFiles/saber_static.dir/saber/thread.cc.o.requires:

.PHONY : CMakeFiles/saber_static.dir/saber/thread.cc.o.requires

CMakeFiles/saber_static.dir/saber/thread.cc.o.provides: CMakeFiles/saber_static.dir/saber/thread.cc.o.requires
	$(MAKE) -f CMakeFiles/saber_static.dir/build.make CMakeFiles/saber_static.dir/saber/thread.cc.o.provides.build
.PHONY : CMakeFiles/saber_static.dir/saber/thread.cc.o.provides

CMakeFiles/saber_static.dir/saber/thread.cc.o.provides.build: CMakeFiles/saber_static.dir/saber/thread.cc.o


CMakeFiles/saber_static.dir/saber/fiber.cc.o: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/fiber.cc.o: ../saber/fiber.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/saber_static.dir/saber/fiber.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber_static.dir/saber/fiber.cc.o -c /home/beecaffe/src/saber/saber/fiber.cc

CMakeFiles/saber_static.dir/saber/fiber.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/fiber.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/fiber.cc > CMakeFiles/saber_static.dir/saber/fiber.cc.i

CMakeFiles/saber_static.dir/saber/fiber.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/fiber.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/fiber.cc -o CMakeFiles/saber_static.dir/saber/fiber.cc.s

CMakeFiles/saber_static.dir/saber/fiber.cc.o.requires:

.PHONY : CMakeFiles/saber_static.dir/saber/fiber.cc.o.requires

CMakeFiles/saber_static.dir/saber/fiber.cc.o.provides: CMakeFiles/saber_static.dir/saber/fiber.cc.o.requires
	$(MAKE) -f CMakeFiles/saber_static.dir/build.make CMakeFiles/saber_static.dir/saber/fiber.cc.o.provides.build
.PHONY : CMakeFiles/saber_static.dir/saber/fiber.cc.o.provides

CMakeFiles/saber_static.dir/saber/fiber.cc.o.provides.build: CMakeFiles/saber_static.dir/saber/fiber.cc.o


CMakeFiles/saber_static.dir/saber/scheduler.cc.o: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/scheduler.cc.o: ../saber/scheduler.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/saber_static.dir/saber/scheduler.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber_static.dir/saber/scheduler.cc.o -c /home/beecaffe/src/saber/saber/scheduler.cc

CMakeFiles/saber_static.dir/saber/scheduler.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/scheduler.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/scheduler.cc > CMakeFiles/saber_static.dir/saber/scheduler.cc.i

CMakeFiles/saber_static.dir/saber/scheduler.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/scheduler.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/scheduler.cc -o CMakeFiles/saber_static.dir/saber/scheduler.cc.s

CMakeFiles/saber_static.dir/saber/scheduler.cc.o.requires:

.PHONY : CMakeFiles/saber_static.dir/saber/scheduler.cc.o.requires

CMakeFiles/saber_static.dir/saber/scheduler.cc.o.provides: CMakeFiles/saber_static.dir/saber/scheduler.cc.o.requires
	$(MAKE) -f CMakeFiles/saber_static.dir/build.make CMakeFiles/saber_static.dir/saber/scheduler.cc.o.provides.build
.PHONY : CMakeFiles/saber_static.dir/saber/scheduler.cc.o.provides

CMakeFiles/saber_static.dir/saber/scheduler.cc.o.provides.build: CMakeFiles/saber_static.dir/saber/scheduler.cc.o


CMakeFiles/saber_static.dir/saber/iomanager.cc.o: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/iomanager.cc.o: ../saber/iomanager.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/saber_static.dir/saber/iomanager.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber_static.dir/saber/iomanager.cc.o -c /home/beecaffe/src/saber/saber/iomanager.cc

CMakeFiles/saber_static.dir/saber/iomanager.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/iomanager.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/iomanager.cc > CMakeFiles/saber_static.dir/saber/iomanager.cc.i

CMakeFiles/saber_static.dir/saber/iomanager.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/iomanager.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/iomanager.cc -o CMakeFiles/saber_static.dir/saber/iomanager.cc.s

CMakeFiles/saber_static.dir/saber/iomanager.cc.o.requires:

.PHONY : CMakeFiles/saber_static.dir/saber/iomanager.cc.o.requires

CMakeFiles/saber_static.dir/saber/iomanager.cc.o.provides: CMakeFiles/saber_static.dir/saber/iomanager.cc.o.requires
	$(MAKE) -f CMakeFiles/saber_static.dir/build.make CMakeFiles/saber_static.dir/saber/iomanager.cc.o.provides.build
.PHONY : CMakeFiles/saber_static.dir/saber/iomanager.cc.o.provides

CMakeFiles/saber_static.dir/saber/iomanager.cc.o.provides.build: CMakeFiles/saber_static.dir/saber/iomanager.cc.o


CMakeFiles/saber_static.dir/saber/timer.cc.o: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/timer.cc.o: ../saber/timer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/saber_static.dir/saber/timer.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/saber_static.dir/saber/timer.cc.o -c /home/beecaffe/src/saber/saber/timer.cc

CMakeFiles/saber_static.dir/saber/timer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/timer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/beecaffe/src/saber/saber/timer.cc > CMakeFiles/saber_static.dir/saber/timer.cc.i

CMakeFiles/saber_static.dir/saber/timer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/timer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/beecaffe/src/saber/saber/timer.cc -o CMakeFiles/saber_static.dir/saber/timer.cc.s

CMakeFiles/saber_static.dir/saber/timer.cc.o.requires:

.PHONY : CMakeFiles/saber_static.dir/saber/timer.cc.o.requires

CMakeFiles/saber_static.dir/saber/timer.cc.o.provides: CMakeFiles/saber_static.dir/saber/timer.cc.o.requires
	$(MAKE) -f CMakeFiles/saber_static.dir/build.make CMakeFiles/saber_static.dir/saber/timer.cc.o.provides.build
.PHONY : CMakeFiles/saber_static.dir/saber/timer.cc.o.provides

CMakeFiles/saber_static.dir/saber/timer.cc.o.provides.build: CMakeFiles/saber_static.dir/saber/timer.cc.o


# Object files for target saber_static
saber_static_OBJECTS = \
"CMakeFiles/saber_static.dir/saber/log.cc.o" \
"CMakeFiles/saber_static.dir/saber/utils.cc.o" \
"CMakeFiles/saber_static.dir/saber/json/json.cc.o" \
"CMakeFiles/saber_static.dir/saber/config.cc.o" \
"CMakeFiles/saber_static.dir/saber/thread.cc.o" \
"CMakeFiles/saber_static.dir/saber/fiber.cc.o" \
"CMakeFiles/saber_static.dir/saber/scheduler.cc.o" \
"CMakeFiles/saber_static.dir/saber/iomanager.cc.o" \
"CMakeFiles/saber_static.dir/saber/timer.cc.o"

# External object files for target saber_static
saber_static_EXTERNAL_OBJECTS =

../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/log.cc.o
../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/utils.cc.o
../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/json/json.cc.o
../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/config.cc.o
../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/thread.cc.o
../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/fiber.cc.o
../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/scheduler.cc.o
../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/iomanager.cc.o
../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/timer.cc.o
../lib/libsaber.a: CMakeFiles/saber_static.dir/build.make
../lib/libsaber.a: CMakeFiles/saber_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/beecaffe/src/saber/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library ../lib/libsaber.a"
	$(CMAKE_COMMAND) -P CMakeFiles/saber_static.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/saber_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/saber_static.dir/build: ../lib/libsaber.a

.PHONY : CMakeFiles/saber_static.dir/build

CMakeFiles/saber_static.dir/requires: CMakeFiles/saber_static.dir/saber/log.cc.o.requires
CMakeFiles/saber_static.dir/requires: CMakeFiles/saber_static.dir/saber/utils.cc.o.requires
CMakeFiles/saber_static.dir/requires: CMakeFiles/saber_static.dir/saber/json/json.cc.o.requires
CMakeFiles/saber_static.dir/requires: CMakeFiles/saber_static.dir/saber/config.cc.o.requires
CMakeFiles/saber_static.dir/requires: CMakeFiles/saber_static.dir/saber/thread.cc.o.requires
CMakeFiles/saber_static.dir/requires: CMakeFiles/saber_static.dir/saber/fiber.cc.o.requires
CMakeFiles/saber_static.dir/requires: CMakeFiles/saber_static.dir/saber/scheduler.cc.o.requires
CMakeFiles/saber_static.dir/requires: CMakeFiles/saber_static.dir/saber/iomanager.cc.o.requires
CMakeFiles/saber_static.dir/requires: CMakeFiles/saber_static.dir/saber/timer.cc.o.requires

.PHONY : CMakeFiles/saber_static.dir/requires

CMakeFiles/saber_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/saber_static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/saber_static.dir/clean

CMakeFiles/saber_static.dir/depend:
	cd /home/beecaffe/src/saber/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/beecaffe/src/saber /home/beecaffe/src/saber /home/beecaffe/src/saber/build /home/beecaffe/src/saber/build /home/beecaffe/src/saber/build/CMakeFiles/saber_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/saber_static.dir/depend

