# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\ClionProjects\saber

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\ClionProjects\saber\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/saber_static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/saber_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/saber_static.dir/flags.make

CMakeFiles/saber_static.dir/saber/log.cc.obj: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/log.cc.obj: ../saber/log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ClionProjects\saber\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/saber_static.dir/saber/log.cc.obj"
	C:\MinGw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\saber_static.dir\saber\log.cc.obj -c D:\ClionProjects\saber\saber\log.cc

CMakeFiles/saber_static.dir/saber/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/log.cc.i"
	C:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ClionProjects\saber\saber\log.cc > CMakeFiles\saber_static.dir\saber\log.cc.i

CMakeFiles/saber_static.dir/saber/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/log.cc.s"
	C:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ClionProjects\saber\saber\log.cc -o CMakeFiles\saber_static.dir\saber\log.cc.s

CMakeFiles/saber_static.dir/saber/utils.cc.obj: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/utils.cc.obj: ../saber/utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ClionProjects\saber\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/saber_static.dir/saber/utils.cc.obj"
	C:\MinGw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\saber_static.dir\saber\utils.cc.obj -c D:\ClionProjects\saber\saber\utils.cc

CMakeFiles/saber_static.dir/saber/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/utils.cc.i"
	C:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ClionProjects\saber\saber\utils.cc > CMakeFiles\saber_static.dir\saber\utils.cc.i

CMakeFiles/saber_static.dir/saber/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/utils.cc.s"
	C:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ClionProjects\saber\saber\utils.cc -o CMakeFiles\saber_static.dir\saber\utils.cc.s

CMakeFiles/saber_static.dir/saber/json/json.cc.obj: CMakeFiles/saber_static.dir/flags.make
CMakeFiles/saber_static.dir/saber/json/json.cc.obj: ../saber/json/json.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ClionProjects\saber\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/saber_static.dir/saber/json/json.cc.obj"
	C:\MinGw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\saber_static.dir\saber\json\json.cc.obj -c D:\ClionProjects\saber\saber\json\json.cc

CMakeFiles/saber_static.dir/saber/json/json.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/saber_static.dir/saber/json/json.cc.i"
	C:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\ClionProjects\saber\saber\json\json.cc > CMakeFiles\saber_static.dir\saber\json\json.cc.i

CMakeFiles/saber_static.dir/saber/json/json.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/saber_static.dir/saber/json/json.cc.s"
	C:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\ClionProjects\saber\saber\json\json.cc -o CMakeFiles\saber_static.dir\saber\json\json.cc.s

# Object files for target saber_static
saber_static_OBJECTS = \
"CMakeFiles/saber_static.dir/saber/log.cc.obj" \
"CMakeFiles/saber_static.dir/saber/utils.cc.obj" \
"CMakeFiles/saber_static.dir/saber/json/json.cc.obj"

# External object files for target saber_static
saber_static_EXTERNAL_OBJECTS =

../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/log.cc.obj
../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/utils.cc.obj
../lib/libsaber.a: CMakeFiles/saber_static.dir/saber/json/json.cc.obj
../lib/libsaber.a: CMakeFiles/saber_static.dir/build.make
../lib/libsaber.a: CMakeFiles/saber_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\ClionProjects\saber\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ..\lib\libsaber.a"
	$(CMAKE_COMMAND) -P CMakeFiles\saber_static.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\saber_static.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/saber_static.dir/build: ../lib/libsaber.a

.PHONY : CMakeFiles/saber_static.dir/build

CMakeFiles/saber_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\saber_static.dir\cmake_clean.cmake
.PHONY : CMakeFiles/saber_static.dir/clean

CMakeFiles/saber_static.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\ClionProjects\saber D:\ClionProjects\saber D:\ClionProjects\saber\cmake-build-debug D:\ClionProjects\saber\cmake-build-debug D:\ClionProjects\saber\cmake-build-debug\CMakeFiles\saber_static.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/saber_static.dir/depend

