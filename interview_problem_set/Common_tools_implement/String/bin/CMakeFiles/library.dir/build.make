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
CMAKE_SOURCE_DIR = /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String/bin

# Include any dependencies generated for this target.
include CMakeFiles/library.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/library.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/library.dir/flags.make

CMakeFiles/library.dir/string.cpp.o: CMakeFiles/library.dir/flags.make
CMakeFiles/library.dir/string.cpp.o: ../string.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/library.dir/string.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/library.dir/string.cpp.o -c /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String/string.cpp

CMakeFiles/library.dir/string.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/library.dir/string.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String/string.cpp > CMakeFiles/library.dir/string.cpp.i

CMakeFiles/library.dir/string.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/library.dir/string.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String/string.cpp -o CMakeFiles/library.dir/string.cpp.s

CMakeFiles/library.dir/string.cpp.o.requires:

.PHONY : CMakeFiles/library.dir/string.cpp.o.requires

CMakeFiles/library.dir/string.cpp.o.provides: CMakeFiles/library.dir/string.cpp.o.requires
	$(MAKE) -f CMakeFiles/library.dir/build.make CMakeFiles/library.dir/string.cpp.o.provides.build
.PHONY : CMakeFiles/library.dir/string.cpp.o.provides

CMakeFiles/library.dir/string.cpp.o.provides.build: CMakeFiles/library.dir/string.cpp.o


# Object files for target library
library_OBJECTS = \
"CMakeFiles/library.dir/string.cpp.o"

# External object files for target library
library_EXTERNAL_OBJECTS =

liblibrary.a: CMakeFiles/library.dir/string.cpp.o
liblibrary.a: CMakeFiles/library.dir/build.make
liblibrary.a: CMakeFiles/library.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblibrary.a"
	$(CMAKE_COMMAND) -P CMakeFiles/library.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/library.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/library.dir/build: liblibrary.a

.PHONY : CMakeFiles/library.dir/build

CMakeFiles/library.dir/requires: CMakeFiles/library.dir/string.cpp.o.requires

.PHONY : CMakeFiles/library.dir/requires

CMakeFiles/library.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/library.dir/cmake_clean.cmake
.PHONY : CMakeFiles/library.dir/clean

CMakeFiles/library.dir/depend:
	cd /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String/bin /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String/bin /home/frank/GitRootPath/Practice/interview_problem_set/Common_tools_implement/String/bin/CMakeFiles/library.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/library.dir/depend
