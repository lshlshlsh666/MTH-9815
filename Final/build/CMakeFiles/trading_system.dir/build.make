# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/lshlshlsh/Desktop/MTH 9815/Final"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/lshlshlsh/Desktop/MTH 9815/Final/build"

# Include any dependencies generated for this target.
include CMakeFiles/trading_system.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/trading_system.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/trading_system.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/trading_system.dir/flags.make

CMakeFiles/trading_system.dir/codegen:
.PHONY : CMakeFiles/trading_system.dir/codegen

CMakeFiles/trading_system.dir/main.o: CMakeFiles/trading_system.dir/flags.make
CMakeFiles/trading_system.dir/main.o: /Users/lshlshlsh/Desktop/MTH\ 9815/Final/main.cpp
CMakeFiles/trading_system.dir/main.o: CMakeFiles/trading_system.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/lshlshlsh/Desktop/MTH 9815/Final/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/trading_system.dir/main.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/trading_system.dir/main.o -MF CMakeFiles/trading_system.dir/main.o.d -o CMakeFiles/trading_system.dir/main.o -c "/Users/lshlshlsh/Desktop/MTH 9815/Final/main.cpp"

CMakeFiles/trading_system.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/trading_system.dir/main.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/lshlshlsh/Desktop/MTH 9815/Final/main.cpp" > CMakeFiles/trading_system.dir/main.i

CMakeFiles/trading_system.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/trading_system.dir/main.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/lshlshlsh/Desktop/MTH 9815/Final/main.cpp" -o CMakeFiles/trading_system.dir/main.s

# Object files for target trading_system
trading_system_OBJECTS = \
"CMakeFiles/trading_system.dir/main.o"

# External object files for target trading_system
trading_system_EXTERNAL_OBJECTS =

trading_system: CMakeFiles/trading_system.dir/main.o
trading_system: CMakeFiles/trading_system.dir/build.make
trading_system: CMakeFiles/trading_system.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/lshlshlsh/Desktop/MTH 9815/Final/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable trading_system"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trading_system.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/trading_system.dir/build: trading_system
.PHONY : CMakeFiles/trading_system.dir/build

CMakeFiles/trading_system.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/trading_system.dir/cmake_clean.cmake
.PHONY : CMakeFiles/trading_system.dir/clean

CMakeFiles/trading_system.dir/depend:
	cd "/Users/lshlshlsh/Desktop/MTH 9815/Final/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/lshlshlsh/Desktop/MTH 9815/Final" "/Users/lshlshlsh/Desktop/MTH 9815/Final" "/Users/lshlshlsh/Desktop/MTH 9815/Final/build" "/Users/lshlshlsh/Desktop/MTH 9815/Final/build" "/Users/lshlshlsh/Desktop/MTH 9815/Final/build/CMakeFiles/trading_system.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/trading_system.dir/depend

