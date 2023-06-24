# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /Dysk_przenośny/Programowanie/C++/TrainPath_V2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build

# Include any dependencies generated for this target.
include Contact_With_DB/CMakeFiles/ContactDB.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Contact_With_DB/CMakeFiles/ContactDB.dir/compiler_depend.make

# Include the progress variables for this target.
include Contact_With_DB/CMakeFiles/ContactDB.dir/progress.make

# Include the compile flags for this target's objects.
include Contact_With_DB/CMakeFiles/ContactDB.dir/flags.make

Contact_With_DB/CMakeFiles/ContactDB.dir/contact_with_db.cpp.o: Contact_With_DB/CMakeFiles/ContactDB.dir/flags.make
Contact_With_DB/CMakeFiles/ContactDB.dir/contact_with_db.cpp.o: /Dysk_przenośny/Programowanie/C++/TrainPath_V2/Contact_With_DB/contact_with_db.cpp
Contact_With_DB/CMakeFiles/ContactDB.dir/contact_with_db.cpp.o: Contact_With_DB/CMakeFiles/ContactDB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Dysk_przenośny/Programowanie/C++/TrainPath_V2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Contact_With_DB/CMakeFiles/ContactDB.dir/contact_with_db.cpp.o"
	cd /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build/Contact_With_DB && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Contact_With_DB/CMakeFiles/ContactDB.dir/contact_with_db.cpp.o -MF CMakeFiles/ContactDB.dir/contact_with_db.cpp.o.d -o CMakeFiles/ContactDB.dir/contact_with_db.cpp.o -c /Dysk_przenośny/Programowanie/C++/TrainPath_V2/Contact_With_DB/contact_with_db.cpp

Contact_With_DB/CMakeFiles/ContactDB.dir/contact_with_db.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ContactDB.dir/contact_with_db.cpp.i"
	cd /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build/Contact_With_DB && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Dysk_przenośny/Programowanie/C++/TrainPath_V2/Contact_With_DB/contact_with_db.cpp > CMakeFiles/ContactDB.dir/contact_with_db.cpp.i

Contact_With_DB/CMakeFiles/ContactDB.dir/contact_with_db.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ContactDB.dir/contact_with_db.cpp.s"
	cd /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build/Contact_With_DB && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Dysk_przenośny/Programowanie/C++/TrainPath_V2/Contact_With_DB/contact_with_db.cpp -o CMakeFiles/ContactDB.dir/contact_with_db.cpp.s

# Object files for target ContactDB
ContactDB_OBJECTS = \
"CMakeFiles/ContactDB.dir/contact_with_db.cpp.o"

# External object files for target ContactDB
ContactDB_EXTERNAL_OBJECTS =

Contact_With_DB/libContactDB.a: Contact_With_DB/CMakeFiles/ContactDB.dir/contact_with_db.cpp.o
Contact_With_DB/libContactDB.a: Contact_With_DB/CMakeFiles/ContactDB.dir/build.make
Contact_With_DB/libContactDB.a: Contact_With_DB/CMakeFiles/ContactDB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Dysk_przenośny/Programowanie/C++/TrainPath_V2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libContactDB.a"
	cd /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build/Contact_With_DB && $(CMAKE_COMMAND) -P CMakeFiles/ContactDB.dir/cmake_clean_target.cmake
	cd /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build/Contact_With_DB && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ContactDB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Contact_With_DB/CMakeFiles/ContactDB.dir/build: Contact_With_DB/libContactDB.a
.PHONY : Contact_With_DB/CMakeFiles/ContactDB.dir/build

Contact_With_DB/CMakeFiles/ContactDB.dir/clean:
	cd /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build/Contact_With_DB && $(CMAKE_COMMAND) -P CMakeFiles/ContactDB.dir/cmake_clean.cmake
.PHONY : Contact_With_DB/CMakeFiles/ContactDB.dir/clean

Contact_With_DB/CMakeFiles/ContactDB.dir/depend:
	cd /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Dysk_przenośny/Programowanie/C++/TrainPath_V2 /Dysk_przenośny/Programowanie/C++/TrainPath_V2/Contact_With_DB /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build/Contact_With_DB /Dysk_przenośny/Programowanie/C++/TrainPath_V2/build/Contact_With_DB/CMakeFiles/ContactDB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Contact_With_DB/CMakeFiles/ContactDB.dir/depend

