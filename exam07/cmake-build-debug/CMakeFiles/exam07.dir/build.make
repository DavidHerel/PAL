# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Skola\PAL\PAL\exam07

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Skola\PAL\PAL\exam07\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\exam07.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\exam07.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\exam07.dir\flags.make

CMakeFiles\exam07.dir\main.cpp.obj: CMakeFiles\exam07.dir\flags.make
CMakeFiles\exam07.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Skola\PAL\PAL\exam07\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exam07.dir/main.cpp.obj"
	D:\VisualStudio\VC\Tools\MSVC\14.26.28801\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\exam07.dir\main.cpp.obj /FdCMakeFiles\exam07.dir\ /FS -c D:\Skola\PAL\PAL\exam07\main.cpp
<<

CMakeFiles\exam07.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exam07.dir/main.cpp.i"
	D:\VisualStudio\VC\Tools\MSVC\14.26.28801\bin\Hostx86\x86\cl.exe > CMakeFiles\exam07.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Skola\PAL\PAL\exam07\main.cpp
<<

CMakeFiles\exam07.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exam07.dir/main.cpp.s"
	D:\VisualStudio\VC\Tools\MSVC\14.26.28801\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\exam07.dir\main.cpp.s /c D:\Skola\PAL\PAL\exam07\main.cpp
<<

# Object files for target exam07
exam07_OBJECTS = \
"CMakeFiles\exam07.dir\main.cpp.obj"

# External object files for target exam07
exam07_EXTERNAL_OBJECTS =

exam07.exe: CMakeFiles\exam07.dir\main.cpp.obj
exam07.exe: CMakeFiles\exam07.dir\build.make
exam07.exe: CMakeFiles\exam07.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Skola\PAL\PAL\exam07\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable exam07.exe"
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\exam07.dir --manifests  -- D:\VisualStudio\VC\Tools\MSVC\14.26.28801\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\exam07.dir\objects1.rsp @<<
 /out:exam07.exe /implib:exam07.lib /pdb:D:\Skola\PAL\PAL\exam07\cmake-build-debug\exam07.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\exam07.dir\build: exam07.exe

.PHONY : CMakeFiles\exam07.dir\build

CMakeFiles\exam07.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\exam07.dir\cmake_clean.cmake
.PHONY : CMakeFiles\exam07.dir\clean

CMakeFiles\exam07.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\Skola\PAL\PAL\exam07 D:\Skola\PAL\PAL\exam07 D:\Skola\PAL\PAL\exam07\cmake-build-debug D:\Skola\PAL\PAL\exam07\cmake-build-debug D:\Skola\PAL\PAL\exam07\cmake-build-debug\CMakeFiles\exam07.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\exam07.dir\depend
