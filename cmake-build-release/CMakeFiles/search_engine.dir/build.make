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
CMAKE_SOURCE_DIR = /mnt/c/CLionProjects/21s-srch-eng-csphalopods

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/CLionProjects/21s-srch-eng-csphalopods/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/search_engine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/search_engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/search_engine.dir/flags.make

CMakeFiles/search_engine.dir/main.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CLionProjects/21s-srch-eng-csphalopods/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/search_engine.dir/main.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/main.cpp.o -c /mnt/c/CLionProjects/21s-srch-eng-csphalopods/main.cpp

CMakeFiles/search_engine.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/main.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CLionProjects/21s-srch-eng-csphalopods/main.cpp > CMakeFiles/search_engine.dir/main.cpp.i

CMakeFiles/search_engine.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/main.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CLionProjects/21s-srch-eng-csphalopods/main.cpp -o CMakeFiles/search_engine.dir/main.cpp.s

CMakeFiles/search_engine.dir/Runner.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/Runner.cpp.o: ../Runner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CLionProjects/21s-srch-eng-csphalopods/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/search_engine.dir/Runner.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/Runner.cpp.o -c /mnt/c/CLionProjects/21s-srch-eng-csphalopods/Runner.cpp

CMakeFiles/search_engine.dir/Runner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/Runner.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CLionProjects/21s-srch-eng-csphalopods/Runner.cpp > CMakeFiles/search_engine.dir/Runner.cpp.i

CMakeFiles/search_engine.dir/Runner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/Runner.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CLionProjects/21s-srch-eng-csphalopods/Runner.cpp -o CMakeFiles/search_engine.dir/Runner.cpp.s

CMakeFiles/search_engine.dir/UserInterface.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/UserInterface.cpp.o: ../UserInterface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CLionProjects/21s-srch-eng-csphalopods/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/search_engine.dir/UserInterface.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/UserInterface.cpp.o -c /mnt/c/CLionProjects/21s-srch-eng-csphalopods/UserInterface.cpp

CMakeFiles/search_engine.dir/UserInterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/UserInterface.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CLionProjects/21s-srch-eng-csphalopods/UserInterface.cpp > CMakeFiles/search_engine.dir/UserInterface.cpp.i

CMakeFiles/search_engine.dir/UserInterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/UserInterface.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CLionProjects/21s-srch-eng-csphalopods/UserInterface.cpp -o CMakeFiles/search_engine.dir/UserInterface.cpp.s

CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o: ../porter2_stemmer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CLionProjects/21s-srch-eng-csphalopods/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o -c /mnt/c/CLionProjects/21s-srch-eng-csphalopods/porter2_stemmer.cpp

CMakeFiles/search_engine.dir/porter2_stemmer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/porter2_stemmer.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CLionProjects/21s-srch-eng-csphalopods/porter2_stemmer.cpp > CMakeFiles/search_engine.dir/porter2_stemmer.cpp.i

CMakeFiles/search_engine.dir/porter2_stemmer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/porter2_stemmer.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CLionProjects/21s-srch-eng-csphalopods/porter2_stemmer.cpp -o CMakeFiles/search_engine.dir/porter2_stemmer.cpp.s

# Object files for target search_engine
search_engine_OBJECTS = \
"CMakeFiles/search_engine.dir/main.cpp.o" \
"CMakeFiles/search_engine.dir/Runner.cpp.o" \
"CMakeFiles/search_engine.dir/UserInterface.cpp.o" \
"CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o"

# External object files for target search_engine
search_engine_EXTERNAL_OBJECTS =

search_engine: CMakeFiles/search_engine.dir/main.cpp.o
search_engine: CMakeFiles/search_engine.dir/Runner.cpp.o
search_engine: CMakeFiles/search_engine.dir/UserInterface.cpp.o
search_engine: CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o
search_engine: CMakeFiles/search_engine.dir/build.make
search_engine: CMakeFiles/search_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/CLionProjects/21s-srch-eng-csphalopods/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable search_engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/search_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/search_engine.dir/build: search_engine

.PHONY : CMakeFiles/search_engine.dir/build

CMakeFiles/search_engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/search_engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/search_engine.dir/clean

CMakeFiles/search_engine.dir/depend:
	cd /mnt/c/CLionProjects/21s-srch-eng-csphalopods/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/CLionProjects/21s-srch-eng-csphalopods /mnt/c/CLionProjects/21s-srch-eng-csphalopods /mnt/c/CLionProjects/21s-srch-eng-csphalopods/cmake-build-release /mnt/c/CLionProjects/21s-srch-eng-csphalopods/cmake-build-release /mnt/c/CLionProjects/21s-srch-eng-csphalopods/cmake-build-release/CMakeFiles/search_engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/search_engine.dir/depend

