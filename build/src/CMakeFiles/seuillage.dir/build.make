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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/local.isima.fr/vicanhotod/TP_GeoAlgo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/local.isima.fr/vicanhotod/TP_GeoAlgo/build

# Include any dependencies generated for this target.
include src/CMakeFiles/seuillage.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/seuillage.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/seuillage.dir/flags.make

src/CMakeFiles/seuillage.dir/seuillage.cpp.o: src/CMakeFiles/seuillage.dir/flags.make
src/CMakeFiles/seuillage.dir/seuillage.cpp.o: ../src/seuillage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/seuillage.dir/seuillage.cpp.o"
	cd /home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/seuillage.dir/seuillage.cpp.o -c /home/local.isima.fr/vicanhotod/TP_GeoAlgo/src/seuillage.cpp

src/CMakeFiles/seuillage.dir/seuillage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/seuillage.dir/seuillage.cpp.i"
	cd /home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/local.isima.fr/vicanhotod/TP_GeoAlgo/src/seuillage.cpp > CMakeFiles/seuillage.dir/seuillage.cpp.i

src/CMakeFiles/seuillage.dir/seuillage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/seuillage.dir/seuillage.cpp.s"
	cd /home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/local.isima.fr/vicanhotod/TP_GeoAlgo/src/seuillage.cpp -o CMakeFiles/seuillage.dir/seuillage.cpp.s

# Object files for target seuillage
seuillage_OBJECTS = \
"CMakeFiles/seuillage.dir/seuillage.cpp.o"

# External object files for target seuillage
seuillage_EXTERNAL_OBJECTS =

seuillage: src/CMakeFiles/seuillage.dir/seuillage.cpp.o
seuillage: src/CMakeFiles/seuillage.dir/build.make
seuillage: /usr/lib/x86_64-linux-gnu/libgmpxx.so
seuillage: /usr/lib/x86_64-linux-gnu/libmpfr.so
seuillage: /usr/lib/x86_64-linux-gnu/libgmp.so
seuillage: src/CMakeFiles/seuillage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../seuillage"
	cd /home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/seuillage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/seuillage.dir/build: seuillage

.PHONY : src/CMakeFiles/seuillage.dir/build

src/CMakeFiles/seuillage.dir/clean:
	cd /home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/src && $(CMAKE_COMMAND) -P CMakeFiles/seuillage.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/seuillage.dir/clean

src/CMakeFiles/seuillage.dir/depend:
	cd /home/local.isima.fr/vicanhotod/TP_GeoAlgo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/local.isima.fr/vicanhotod/TP_GeoAlgo /home/local.isima.fr/vicanhotod/TP_GeoAlgo/src /home/local.isima.fr/vicanhotod/TP_GeoAlgo/build /home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/src /home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/src/CMakeFiles/seuillage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/seuillage.dir/depend

