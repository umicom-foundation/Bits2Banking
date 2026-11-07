<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/03-separate-source-and-build.md

PURPOSE:
Keep source and build directories separate

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep source and build directories separate

CMake describes how a software project is prepared for building. In this course you will follow a small C project from source files to executables, understand dependencies, run tests and record useful evidence. Every chapter includes the setup needed to enter the exercise directly.

## Start here

A terminal is a window in which you type commands. A folder groups files; a path tells a command where a file or folder is. Source files contain the instructions people edit. A build folder contains the machine-readable results. Keep the two folders separate.

This course uses the existing labs/native/bounded-ledger-line project in Bits2Banking. It decodes a fictional message such as 1001:+2500: training account 1001, with a change of 2500 pence. It does not connect to a bank.

On Windows, install MSYS2. In its UCRT64 terminal install the tools:

~~~bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
~~~

Open PowerShell. Adjust the repository path if your copy is elsewhere. Run each line separately and stop on an error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
gcc --version
ninja --version
cmake -S labs/native/bounded-ledger-line -B build/ledger-line -G Ninja -DBUILD_TESTING=ON
cmake --build build/ledger-line --parallel 2
ctest --test-dir build/ledger-line --output-on-failure --no-tests=error
~~~

Use CMake 3.24 or newer and a compiler with C23 support. On Linux, install these tools through the distribution's package manager, open Bash in the repository, and use the same three cmake/ctest commands. The small project builds independently of Framework. [Learning C](../../../courses/learning-c/index.html) gives a slower installation walkthrough.

The expected test names end in syntax, mutations and example. Missing tools, missing executables and zero selected tests need investigation. For experiments, copy the lab to a separate practice folder and point -S at that folder; preserve the original example.


## The problem

A project contains files people maintain and files tools regenerate. Separating them makes review and troubleshooting easier.

In cmake -S labs/native/bounded-ledger-line -B build/ledger-line, -S selects the directory containing CMakeLists.txt. -B selects the build directory. Relative paths start from the terminal's current folder.

The build directory contains CMakeCache.txt, generated Ninja rules, objects and executables. The cache records local choices such as the compiler and source directory. It is not portable project source.

## Try two configurations

1. Keep the normal build directory.
2. Configure a second directory with cmake -S labs/native/bounded-ledger-line -B build/ledger-line-release -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON.
3. Build it with cmake --build build/ledger-line-release --parallel 2.
4. Inspect both directories. They share source but have independent outputs.
5. Run CTest using the directory you actually built.

A single-configuration Ninja build uses CMAKE_BUILD_TYPE at configuration. Debug typically preserves debugging information; Release enables release settings. Exact flags depend on the compiler and project.

## Paths with spaces

Quote "C:/practice projects/ledger" so the shell passes one argument. Shell quoting differs from C string syntax. A path in a terminal command is not a line of C source.

If CMake reports a different generator or source directory in the cache, choose a new build directory for the new configuration. Keep the previous directory until you have retained its useful logs. Editing build.ninja manually is temporary because CMake can regenerate it.

## Exercise

Write the source and build paths for both configurations. Which files should appear in source review after changing parser behaviour? The parser, its tests and relevant documentation. Generated objects and local caches are not authored changes. Read ignore rules before adding files to Git.

## Read the source

[Open the example source](../../../../labs/native/bounded-ledger-line/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Read a CMake project one command at a time](02-read-a-cmake-project.md) · [Next: Build a target and its required dependencies](04-target-dependencies.md)
