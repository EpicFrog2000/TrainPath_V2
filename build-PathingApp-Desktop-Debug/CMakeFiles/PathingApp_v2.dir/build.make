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
CMAKE_SOURCE_DIR = /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/PathingApp_v2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PathingApp_v2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PathingApp_v2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PathingApp_v2.dir/flags.make

CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.o: CMakeFiles/PathingApp_v2.dir/flags.make
CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.o: PathingApp_v2_autogen/mocs_compilation.cpp
CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.o: CMakeFiles/PathingApp_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.o -MF CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.o -c /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug/PathingApp_v2_autogen/mocs_compilation.cpp

CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug/PathingApp_v2_autogen/mocs_compilation.cpp > CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.i

CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug/PathingApp_v2_autogen/mocs_compilation.cpp -o CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.s

CMakeFiles/PathingApp_v2.dir/main.cpp.o: CMakeFiles/PathingApp_v2.dir/flags.make
CMakeFiles/PathingApp_v2.dir/main.cpp.o: /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/main.cpp
CMakeFiles/PathingApp_v2.dir/main.cpp.o: CMakeFiles/PathingApp_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PathingApp_v2.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathingApp_v2.dir/main.cpp.o -MF CMakeFiles/PathingApp_v2.dir/main.cpp.o.d -o CMakeFiles/PathingApp_v2.dir/main.cpp.o -c /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/main.cpp

CMakeFiles/PathingApp_v2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathingApp_v2.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/main.cpp > CMakeFiles/PathingApp_v2.dir/main.cpp.i

CMakeFiles/PathingApp_v2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathingApp_v2.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/main.cpp -o CMakeFiles/PathingApp_v2.dir/main.cpp.s

CMakeFiles/PathingApp_v2.dir/widget.cpp.o: CMakeFiles/PathingApp_v2.dir/flags.make
CMakeFiles/PathingApp_v2.dir/widget.cpp.o: /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/widget.cpp
CMakeFiles/PathingApp_v2.dir/widget.cpp.o: CMakeFiles/PathingApp_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PathingApp_v2.dir/widget.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathingApp_v2.dir/widget.cpp.o -MF CMakeFiles/PathingApp_v2.dir/widget.cpp.o.d -o CMakeFiles/PathingApp_v2.dir/widget.cpp.o -c /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/widget.cpp

CMakeFiles/PathingApp_v2.dir/widget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathingApp_v2.dir/widget.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/widget.cpp > CMakeFiles/PathingApp_v2.dir/widget.cpp.i

CMakeFiles/PathingApp_v2.dir/widget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathingApp_v2.dir/widget.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/widget.cpp -o CMakeFiles/PathingApp_v2.dir/widget.cpp.s

CMakeFiles/PathingApp_v2.dir/glwidget.cpp.o: CMakeFiles/PathingApp_v2.dir/flags.make
CMakeFiles/PathingApp_v2.dir/glwidget.cpp.o: /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/glwidget.cpp
CMakeFiles/PathingApp_v2.dir/glwidget.cpp.o: CMakeFiles/PathingApp_v2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PathingApp_v2.dir/glwidget.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PathingApp_v2.dir/glwidget.cpp.o -MF CMakeFiles/PathingApp_v2.dir/glwidget.cpp.o.d -o CMakeFiles/PathingApp_v2.dir/glwidget.cpp.o -c /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/glwidget.cpp

CMakeFiles/PathingApp_v2.dir/glwidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PathingApp_v2.dir/glwidget.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/glwidget.cpp > CMakeFiles/PathingApp_v2.dir/glwidget.cpp.i

CMakeFiles/PathingApp_v2.dir/glwidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PathingApp_v2.dir/glwidget.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp/glwidget.cpp -o CMakeFiles/PathingApp_v2.dir/glwidget.cpp.s

# Object files for target PathingApp_v2
PathingApp_v2_OBJECTS = \
"CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/PathingApp_v2.dir/main.cpp.o" \
"CMakeFiles/PathingApp_v2.dir/widget.cpp.o" \
"CMakeFiles/PathingApp_v2.dir/glwidget.cpp.o"

# External object files for target PathingApp_v2
PathingApp_v2_EXTERNAL_OBJECTS =

PathingApp_v2: CMakeFiles/PathingApp_v2.dir/PathingApp_v2_autogen/mocs_compilation.cpp.o
PathingApp_v2: CMakeFiles/PathingApp_v2.dir/main.cpp.o
PathingApp_v2: CMakeFiles/PathingApp_v2.dir/widget.cpp.o
PathingApp_v2: CMakeFiles/PathingApp_v2.dir/glwidget.cpp.o
PathingApp_v2: CMakeFiles/PathingApp_v2.dir/build.make
PathingApp_v2: /usr/lib/libQt6OpenGLWidgets.so.6.5.0
PathingApp_v2: /usr/lib/libQt6Widgets.so.6.5.0
PathingApp_v2: Drawing_Map/libDrawFunctions.a
PathingApp_v2: Contact_With_DB/libContactDB.a
PathingApp_v2: destination_functions/libDestinationFunctions.a
PathingApp_v2: /usr/lib/libQt6OpenGL.so.6.5.0
PathingApp_v2: /usr/lib/libQt6Gui.so.6.5.0
PathingApp_v2: /usr/lib/libQt6Core.so.6.5.0
PathingApp_v2: /usr/lib/libGLX.so
PathingApp_v2: /usr/lib/libOpenGL.so
PathingApp_v2: CMakeFiles/PathingApp_v2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable PathingApp_v2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PathingApp_v2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PathingApp_v2.dir/build: PathingApp_v2
.PHONY : CMakeFiles/PathingApp_v2.dir/build

CMakeFiles/PathingApp_v2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PathingApp_v2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PathingApp_v2.dir/clean

CMakeFiles/PathingApp_v2.dir/depend:
	cd /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/PathingApp /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug /Dysk_przenośny/Programowanie/C++/OpenGL/GuiOpenGl/PathingApp_v2/build-PathingApp-Desktop-Debug/CMakeFiles/PathingApp_v2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PathingApp_v2.dir/depend

