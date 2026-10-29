# Introduction to CMake

## What CMake does

A compiler translates source. A linker combines translated objects and libraries. CMake describes how those steps belong together. A build tool such as Ninja runs the resulting work. CTest runs the tests registered by the project.

Think of a recipe, prepared ingredients and cooking as different stages. CMake configuration prepares the build instructions. Building carries them out. Testing checks specific results. Installing copies selected artifacts to a destination. Running launches a program for use.

~~~text
CMakeLists.txt + compiler choice
              |
       cmake -S ... -B ...
              |
     build.ninja + CMakeCache.txt
              |
       cmake --build ...
              |
        executable/library
              |
     ctest or manual application use
~~~

## Read a real build description

Open [the activity CMakeLists.txt](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/CMakeLists.txt).

1. cmake_minimum_required declares the minimum CMake language/tool behaviour the project uses.
2. project gives the project a name and declares C as its source language.
3. CMAKE_C_STANDARD selects C23. CMAKE_C_STANDARD_REQUIRED prevents silent fallback to an older language mode.
4. include(CTest) provides testing support and its BUILD_TESTING option.
5. find_package requests an installed Umicom Framework with the base component. REQUIRED means configuration stops if that dependency is unavailable.
6. add_library creates the shared activity-logic target.
7. add_executable creates a console target from console.c.
8. target_link_libraries connects the executable to its library. The library carries its Framework dependency to consumers.
9. add_test registers a command with CTest; it does not execute the test during configuration.

PUBLIC on a library dependency means that both the library and its consumers need that dependency's usage requirements. PRIVATE means it is needed to build that target but is not part of the interface promised to consumers.

## Read a configure command

After installing the Framework SDK, configure the lab:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\framework-activity" -B ".\build\framework-activity" -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework;C:/msys64/ucrt64" -DBUILD_TESTING=ON
~~~

-S names the source folder containing CMakeLists.txt. -B names a different folder for generated files. -G chooses Ninja. A -D argument sets a cache value. CMAKE_C_COMPILER chooses GCC explicitly. CMAKE_PREFIX_PATH lists places where installed dependencies may be found; quote the semicolon-separated list in PowerShell so it remains one argument.

The cache remembers choices between runs. Reuse it for ordinary incremental builds with the same toolchain. Use a new build folder when switching compiler families; copying another computer's build cache also copies its absolute paths.

## Build and test the small target

~~~powershell
cmake --build ".\build\framework-activity" --parallel 2
ctest --test-dir ".\build\framework-activity" --output-on-failure --no-tests=error
& ".\build\framework-activity\btb-activity-console.exe"
~~~

--parallel 2 allows two build jobs at a time. An incremental build recompiles source whose dependencies changed. It does not need a full clean rebuild after every edit.

The expected console result is Completed exercises: 1. The tests cover the first and last valid counts, the full capacity, invalid input, a null output pointer and an in-place update. --no-tests=error prevents an empty test discovery from looking like success.

## Diagnose the first failed stage

If find_package fails, verify that the SDK install completed and its prefix is correct. If building says build.ninja is missing, go back to the configure error. If a linker reports umi_status_text as missing, examine the imported library and its revision. Do not copy a second definition into the lab to hide the missing dependency.

A preset saves a collection of options for repeated use. It belongs to the current repository. Applications' preset is not automatically an OS preset. Use cmake --list-presets in the repository whose build you are preparing.

**Question:** Does configure success mean the program compiled?

**Answer:** No. Configuration created the build instructions. The compiler and linker run during the build stage.

The [official CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) provides additional exercises. Next, follow [Umicom Framework Development](04-framework-development.md).

[Course contents](index.md)
