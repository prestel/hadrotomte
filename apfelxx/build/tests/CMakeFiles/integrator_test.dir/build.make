# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/prestel/work/2021/hadrotomte/apfelxx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/prestel/work/2021/hadrotomte/apfelxx/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/integrator_test.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/integrator_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/integrator_test.dir/flags.make

tests/CMakeFiles/integrator_test.dir/integrator_test.cc.o: tests/CMakeFiles/integrator_test.dir/flags.make
tests/CMakeFiles/integrator_test.dir/integrator_test.cc.o: ../tests/integrator_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/prestel/work/2021/hadrotomte/apfelxx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/integrator_test.dir/integrator_test.cc.o"
	cd /home/prestel/work/2021/hadrotomte/apfelxx/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/integrator_test.dir/integrator_test.cc.o -c /home/prestel/work/2021/hadrotomte/apfelxx/tests/integrator_test.cc

tests/CMakeFiles/integrator_test.dir/integrator_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/integrator_test.dir/integrator_test.cc.i"
	cd /home/prestel/work/2021/hadrotomte/apfelxx/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/prestel/work/2021/hadrotomte/apfelxx/tests/integrator_test.cc > CMakeFiles/integrator_test.dir/integrator_test.cc.i

tests/CMakeFiles/integrator_test.dir/integrator_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/integrator_test.dir/integrator_test.cc.s"
	cd /home/prestel/work/2021/hadrotomte/apfelxx/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/prestel/work/2021/hadrotomte/apfelxx/tests/integrator_test.cc -o CMakeFiles/integrator_test.dir/integrator_test.cc.s

# Object files for target integrator_test
integrator_test_OBJECTS = \
"CMakeFiles/integrator_test.dir/integrator_test.cc.o"

# External object files for target integrator_test
integrator_test_EXTERNAL_OBJECTS =

tests/integrator_test: tests/CMakeFiles/integrator_test.dir/integrator_test.cc.o
tests/integrator_test: tests/CMakeFiles/integrator_test.dir/build.make
tests/integrator_test: ../lib/libapfelxx.so
tests/integrator_test: tests/CMakeFiles/integrator_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/prestel/work/2021/hadrotomte/apfelxx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable integrator_test"
	cd /home/prestel/work/2021/hadrotomte/apfelxx/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/integrator_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/integrator_test.dir/build: tests/integrator_test

.PHONY : tests/CMakeFiles/integrator_test.dir/build

tests/CMakeFiles/integrator_test.dir/clean:
	cd /home/prestel/work/2021/hadrotomte/apfelxx/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/integrator_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/integrator_test.dir/clean

tests/CMakeFiles/integrator_test.dir/depend:
	cd /home/prestel/work/2021/hadrotomte/apfelxx/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/prestel/work/2021/hadrotomte/apfelxx /home/prestel/work/2021/hadrotomte/apfelxx/tests /home/prestel/work/2021/hadrotomte/apfelxx/build /home/prestel/work/2021/hadrotomte/apfelxx/build/tests /home/prestel/work/2021/hadrotomte/apfelxx/build/tests/CMakeFiles/integrator_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/integrator_test.dir/depend

