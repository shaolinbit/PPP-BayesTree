# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/rmw/Documents/git/PPP-BayesTree/trunk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rmw/Documents/git/PPP-BayesTree/trunk/build

# Utility rule file for testPCGSolver.run.

# Include the progress variables for this target.
include tests/CMakeFiles/testPCGSolver.run.dir/progress.make

tests/CMakeFiles/testPCGSolver.run: tests/testPCGSolver
	cd /home/rmw/Documents/git/PPP-BayesTree/trunk/build/tests && ./testPCGSolver

testPCGSolver.run: tests/CMakeFiles/testPCGSolver.run
testPCGSolver.run: tests/CMakeFiles/testPCGSolver.run.dir/build.make

.PHONY : testPCGSolver.run

# Rule to build all files generated by this target.
tests/CMakeFiles/testPCGSolver.run.dir/build: testPCGSolver.run

.PHONY : tests/CMakeFiles/testPCGSolver.run.dir/build

tests/CMakeFiles/testPCGSolver.run.dir/clean:
	cd /home/rmw/Documents/git/PPP-BayesTree/trunk/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/testPCGSolver.run.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/testPCGSolver.run.dir/clean

tests/CMakeFiles/testPCGSolver.run.dir/depend:
	cd /home/rmw/Documents/git/PPP-BayesTree/trunk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rmw/Documents/git/PPP-BayesTree/trunk /home/rmw/Documents/git/PPP-BayesTree/trunk/tests /home/rmw/Documents/git/PPP-BayesTree/trunk/build /home/rmw/Documents/git/PPP-BayesTree/trunk/build/tests /home/rmw/Documents/git/PPP-BayesTree/trunk/build/tests/CMakeFiles/testPCGSolver.run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/testPCGSolver.run.dir/depend

