# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/msg/workspace/c++project/project4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/msg/workspace/c++project/project4

# Include any dependencies generated for this target.
include CMakeFiles/adventure_game.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/adventure_game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/adventure_game.dir/flags.make

CMakeFiles/adventure_game.dir/adventure_game.cpp.o: CMakeFiles/adventure_game.dir/flags.make
CMakeFiles/adventure_game.dir/adventure_game.cpp.o: adventure_game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/msg/workspace/c++project/project4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/adventure_game.dir/adventure_game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/adventure_game.dir/adventure_game.cpp.o -c /home/msg/workspace/c++project/project4/adventure_game.cpp

CMakeFiles/adventure_game.dir/adventure_game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/adventure_game.dir/adventure_game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/msg/workspace/c++project/project4/adventure_game.cpp > CMakeFiles/adventure_game.dir/adventure_game.cpp.i

CMakeFiles/adventure_game.dir/adventure_game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/adventure_game.dir/adventure_game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/msg/workspace/c++project/project4/adventure_game.cpp -o CMakeFiles/adventure_game.dir/adventure_game.cpp.s

# Object files for target adventure_game
adventure_game_OBJECTS = \
"CMakeFiles/adventure_game.dir/adventure_game.cpp.o"

# External object files for target adventure_game
adventure_game_EXTERNAL_OBJECTS =

adventure_game: CMakeFiles/adventure_game.dir/adventure_game.cpp.o
adventure_game: CMakeFiles/adventure_game.dir/build.make
adventure_game: CMakeFiles/adventure_game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/msg/workspace/c++project/project4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable adventure_game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/adventure_game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/adventure_game.dir/build: adventure_game

.PHONY : CMakeFiles/adventure_game.dir/build

CMakeFiles/adventure_game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/adventure_game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/adventure_game.dir/clean

CMakeFiles/adventure_game.dir/depend:
	cd /home/msg/workspace/c++project/project4 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/msg/workspace/c++project/project4 /home/msg/workspace/c++project/project4 /home/msg/workspace/c++project/project4 /home/msg/workspace/c++project/project4 /home/msg/workspace/c++project/project4/CMakeFiles/adventure_game.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/adventure_game.dir/depend
