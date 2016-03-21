# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/daniel/software/kratos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniel/software/kratos/cmake_build

# Include any dependencies generated for this target.
include external_libraries/zlib/CMakeFiles/zlibstatic.dir/depend.make

# Include the progress variables for this target.
include external_libraries/zlib/CMakeFiles/zlibstatic.dir/progress.make

# Include the compile flags for this target's objects.
include external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make

external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o: ../external_libraries/zlib/adler32.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/adler32.o   -c /home/daniel/software/kratos/external_libraries/zlib/adler32.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/adler32.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/adler32.c > CMakeFiles/zlibstatic.dir/adler32.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/adler32.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/adler32.c -o CMakeFiles/zlibstatic.dir/adler32.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o: ../external_libraries/zlib/compress.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/compress.o   -c /home/daniel/software/kratos/external_libraries/zlib/compress.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/compress.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/compress.c > CMakeFiles/zlibstatic.dir/compress.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/compress.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/compress.c -o CMakeFiles/zlibstatic.dir/compress.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o: ../external_libraries/zlib/crc32.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/crc32.o   -c /home/daniel/software/kratos/external_libraries/zlib/crc32.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/crc32.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/crc32.c > CMakeFiles/zlibstatic.dir/crc32.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/crc32.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/crc32.c -o CMakeFiles/zlibstatic.dir/crc32.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o: ../external_libraries/zlib/deflate.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/deflate.o   -c /home/daniel/software/kratos/external_libraries/zlib/deflate.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/deflate.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/deflate.c > CMakeFiles/zlibstatic.dir/deflate.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/deflate.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/deflate.c -o CMakeFiles/zlibstatic.dir/deflate.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o: ../external_libraries/zlib/gzclose.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/gzclose.o   -c /home/daniel/software/kratos/external_libraries/zlib/gzclose.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/gzclose.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/gzclose.c > CMakeFiles/zlibstatic.dir/gzclose.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/gzclose.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/gzclose.c -o CMakeFiles/zlibstatic.dir/gzclose.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o: ../external_libraries/zlib/gzlib.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/gzlib.o   -c /home/daniel/software/kratos/external_libraries/zlib/gzlib.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/gzlib.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/gzlib.c > CMakeFiles/zlibstatic.dir/gzlib.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/gzlib.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/gzlib.c -o CMakeFiles/zlibstatic.dir/gzlib.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o: ../external_libraries/zlib/gzread.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/gzread.o   -c /home/daniel/software/kratos/external_libraries/zlib/gzread.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/gzread.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/gzread.c > CMakeFiles/zlibstatic.dir/gzread.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/gzread.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/gzread.c -o CMakeFiles/zlibstatic.dir/gzread.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o: ../external_libraries/zlib/gzwrite.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/gzwrite.o   -c /home/daniel/software/kratos/external_libraries/zlib/gzwrite.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/gzwrite.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/gzwrite.c > CMakeFiles/zlibstatic.dir/gzwrite.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/gzwrite.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/gzwrite.c -o CMakeFiles/zlibstatic.dir/gzwrite.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o: ../external_libraries/zlib/inflate.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/inflate.o   -c /home/daniel/software/kratos/external_libraries/zlib/inflate.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/inflate.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/inflate.c > CMakeFiles/zlibstatic.dir/inflate.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/inflate.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/inflate.c -o CMakeFiles/zlibstatic.dir/inflate.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o: ../external_libraries/zlib/infback.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/infback.o   -c /home/daniel/software/kratos/external_libraries/zlib/infback.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/infback.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/infback.c > CMakeFiles/zlibstatic.dir/infback.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/infback.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/infback.c -o CMakeFiles/zlibstatic.dir/infback.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o: ../external_libraries/zlib/inftrees.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/inftrees.o   -c /home/daniel/software/kratos/external_libraries/zlib/inftrees.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/inftrees.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/inftrees.c > CMakeFiles/zlibstatic.dir/inftrees.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/inftrees.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/inftrees.c -o CMakeFiles/zlibstatic.dir/inftrees.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o: ../external_libraries/zlib/inffast.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/inffast.o   -c /home/daniel/software/kratos/external_libraries/zlib/inffast.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/inffast.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/inffast.c > CMakeFiles/zlibstatic.dir/inffast.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/inffast.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/inffast.c -o CMakeFiles/zlibstatic.dir/inffast.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o: ../external_libraries/zlib/trees.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/trees.o   -c /home/daniel/software/kratos/external_libraries/zlib/trees.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/trees.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/trees.c > CMakeFiles/zlibstatic.dir/trees.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/trees.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/trees.c -o CMakeFiles/zlibstatic.dir/trees.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o: ../external_libraries/zlib/uncompr.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/uncompr.o   -c /home/daniel/software/kratos/external_libraries/zlib/uncompr.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/uncompr.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/uncompr.c > CMakeFiles/zlibstatic.dir/uncompr.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/uncompr.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/uncompr.c -o CMakeFiles/zlibstatic.dir/uncompr.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o

external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o: external_libraries/zlib/CMakeFiles/zlibstatic.dir/flags.make
external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o: ../external_libraries/zlib/zutil.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/daniel/software/kratos/cmake_build/CMakeFiles $(CMAKE_PROGRESS_15)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/zlibstatic.dir/zutil.o   -c /home/daniel/software/kratos/external_libraries/zlib/zutil.c

external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/zutil.i"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/daniel/software/kratos/external_libraries/zlib/zutil.c > CMakeFiles/zlibstatic.dir/zutil.i

external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/zutil.s"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/daniel/software/kratos/external_libraries/zlib/zutil.c -o CMakeFiles/zlibstatic.dir/zutil.s

external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o.requires:
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o.requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o.provides: external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o.requires
	$(MAKE) -f external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o.provides.build
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o.provides

external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o.provides.build: external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o

# Object files for target zlibstatic
zlibstatic_OBJECTS = \
"CMakeFiles/zlibstatic.dir/adler32.o" \
"CMakeFiles/zlibstatic.dir/compress.o" \
"CMakeFiles/zlibstatic.dir/crc32.o" \
"CMakeFiles/zlibstatic.dir/deflate.o" \
"CMakeFiles/zlibstatic.dir/gzclose.o" \
"CMakeFiles/zlibstatic.dir/gzlib.o" \
"CMakeFiles/zlibstatic.dir/gzread.o" \
"CMakeFiles/zlibstatic.dir/gzwrite.o" \
"CMakeFiles/zlibstatic.dir/inflate.o" \
"CMakeFiles/zlibstatic.dir/infback.o" \
"CMakeFiles/zlibstatic.dir/inftrees.o" \
"CMakeFiles/zlibstatic.dir/inffast.o" \
"CMakeFiles/zlibstatic.dir/trees.o" \
"CMakeFiles/zlibstatic.dir/uncompr.o" \
"CMakeFiles/zlibstatic.dir/zutil.o"

# External object files for target zlibstatic
zlibstatic_EXTERNAL_OBJECTS =

external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/build.make
external_libraries/zlib/libz.a: external_libraries/zlib/CMakeFiles/zlibstatic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libz.a"
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && $(CMAKE_COMMAND) -P CMakeFiles/zlibstatic.dir/cmake_clean_target.cmake
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zlibstatic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external_libraries/zlib/CMakeFiles/zlibstatic.dir/build: external_libraries/zlib/libz.a
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/build

external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/adler32.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/compress.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/crc32.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/deflate.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzclose.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzlib.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzread.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/gzwrite.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inflate.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/infback.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inftrees.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/inffast.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/trees.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/uncompr.o.requires
external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires: external_libraries/zlib/CMakeFiles/zlibstatic.dir/zutil.o.requires
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/requires

external_libraries/zlib/CMakeFiles/zlibstatic.dir/clean:
	cd /home/daniel/software/kratos/cmake_build/external_libraries/zlib && $(CMAKE_COMMAND) -P CMakeFiles/zlibstatic.dir/cmake_clean.cmake
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/clean

external_libraries/zlib/CMakeFiles/zlibstatic.dir/depend:
	cd /home/daniel/software/kratos/cmake_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniel/software/kratos /home/daniel/software/kratos/external_libraries/zlib /home/daniel/software/kratos/cmake_build /home/daniel/software/kratos/cmake_build/external_libraries/zlib /home/daniel/software/kratos/cmake_build/external_libraries/zlib/CMakeFiles/zlibstatic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external_libraries/zlib/CMakeFiles/zlibstatic.dir/depend

