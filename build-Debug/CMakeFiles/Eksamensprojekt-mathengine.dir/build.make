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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/build-Debug"

# Include any dependencies generated for this target.
include CMakeFiles/Eksamensprojekt-mathengine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Eksamensprojekt-mathengine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Eksamensprojekt-mathengine.dir/flags.make

CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.o: CMakeFiles/Eksamensprojekt-mathengine.dir/flags.make
CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.o: ../application.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/build-Debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.o -c "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/application.cpp"

CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/application.cpp" > CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.i

CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/application.cpp" -o CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.s

CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.o: CMakeFiles/Eksamensprojekt-mathengine.dir/flags.make
CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.o: ../src/expression.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/build-Debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.o -c "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/src/expression.cpp"

CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/src/expression.cpp" > CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.i

CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/src/expression.cpp" -o CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.s

CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.o: CMakeFiles/Eksamensprojekt-mathengine.dir/flags.make
CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.o: ../src/token.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/build-Debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.o -c "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/src/token.cpp"

CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/src/token.cpp" > CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.i

CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/src/token.cpp" -o CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.s

# Object files for target Eksamensprojekt-mathengine
Eksamensprojekt__mathengine_OBJECTS = \
"CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.o" \
"CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.o" \
"CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.o"

# External object files for target Eksamensprojekt-mathengine
Eksamensprojekt__mathengine_EXTERNAL_OBJECTS =

Eksamensprojekt-mathengine: CMakeFiles/Eksamensprojekt-mathengine.dir/application.cpp.o
Eksamensprojekt-mathengine: CMakeFiles/Eksamensprojekt-mathengine.dir/src/expression.cpp.o
Eksamensprojekt-mathengine: CMakeFiles/Eksamensprojekt-mathengine.dir/src/token.cpp.o
Eksamensprojekt-mathengine: CMakeFiles/Eksamensprojekt-mathengine.dir/build.make
Eksamensprojekt-mathengine: CMakeFiles/Eksamensprojekt-mathengine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/build-Debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Eksamensprojekt-mathengine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Eksamensprojekt-mathengine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Eksamensprojekt-mathengine.dir/build: Eksamensprojekt-mathengine

.PHONY : CMakeFiles/Eksamensprojekt-mathengine.dir/build

CMakeFiles/Eksamensprojekt-mathengine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Eksamensprojekt-mathengine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Eksamensprojekt-mathengine.dir/clean

CMakeFiles/Eksamensprojekt-mathengine.dir/depend:
	cd "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/build-Debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor" "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor" "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/build-Debug" "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/build-Debug" "/Users/haim/Desktop/Skole/HTX 3.g/Programmering/eksamensprojekt-matematik-motor/build-Debug/CMakeFiles/Eksamensprojekt-mathengine.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Eksamensprojekt-mathengine.dir/depend
