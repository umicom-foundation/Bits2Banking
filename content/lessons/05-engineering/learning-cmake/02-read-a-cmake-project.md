<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/02-read-a-cmake-project.md

PURPOSE:
Read a CMake project one command at a time

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read a CMake project one command at a time

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


## Goal

Connect the lab's build description to visible files and results. A CMake command has a name followed by arguments in parentheses.

cmake_minimum_required(VERSION 3.24) states the oldest supported CMake release. project(Bits2BankingLedgerLine LANGUAGES C) names the project and configures a C compiler. The project name is not an executable filename.

include(CTest) enables normal testing setup and provides BUILD_TESTING. add_library(btb_ledger_line STATIC ledger_line.c) creates a static-library target. A target is a named result in the build graph. A static library collects compiled objects for later linking.

add_executable(bits2banking-ledger-line-demo main.c) defines a program. target_link_libraries connects it to btb_ledger_line. The application does not copy the parser into main.c.

## Inspect the graph

1. Open CMakeLists.txt.
2. Locate the three add_executable calls: demo, test and fuzz.
3. Draw an arrow from each to btb_ledger_line.
4. Find ledger_line.c. It has one compilation owner in this graph.
5. Read the filenames used by the test and fuzz targets.

The foreach block applies settings to each target. C_STANDARD 23 requests C23. C_STANDARD_REQUIRED ON refuses fallback to an older standard. C_EXTENSIONS OFF requests standard language mode rather than additional compiler extensions.

## Experiment

In a practice copy rename the demo target consistently in add_executable, target_link_libraries, the foreach list and add_test. Configure and build again. Observe the new output name.

If a reference keeps the old name, configuration may report an unknown target, or a later test may try to execute a nonexistent command. Compare with the original build file to recover.

## Recap

A target identifies a build result; a source path identifies an input. They need not have the same name. Does project(...) create a program? No: add_executable defines that result.

## Read the source

[Open the example source](../../../../labs/native/bounded-ledger-line/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Follow source files to a running program](01-follow-source-to-program.md) · [Next: Keep source and build directories separate](03-separate-source-and-build.md)
