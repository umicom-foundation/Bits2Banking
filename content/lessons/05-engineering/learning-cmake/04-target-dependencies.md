<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/04-target-dependencies.md

PURPOSE:
Build a target and its required dependencies

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Build a target and its required dependencies

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

Request one program while letting the build tool identify its prerequisites.

The demo depends on btb_ledger_line through target_link_libraries. The test and mutation programs depend on the same library. That library depends on ledger_line.c and the headers it includes.

~~~powershell
cmake --build build/ledger-line --target bits2banking-ledger-line-demo --parallel 2
~~~

This selects the demo. Its parser dependency is still built when necessary.

## Observe changes

1. Build the demo.
2. Run the command again. With unchanged inputs and configuration, Ninja normally reports no work.
3. Change only main.c in a practice copy. Rebuild and observe the compilation and linking steps.
4. Change ledger_line.c. The shared object and library now need updating.
5. Build the test targets and run their tests, because they also depend on the parser.

A header change can trigger several compilations. A comment change can also trigger recompilation when timestamps drive the graph. Incremental building follows dependencies; it does not prove two source versions have identical meaning.

## Avoid stale results

Removing a dependency to make builds faster can produce stale programs. Prefer accurate target links, smaller libraries and separate build directories. Record what actually rebuilt rather than interpreting every progress line as a full rebuild.

Studio's project build service can select a project recipe and invoke its graph. Framework owns reusable orchestration. A small lesson project does not need to rebuild the ecosystem to exercise its parser.

## Question

If main.c is unchanged but the parser changes, should the demo be relinked? Yes. Its behaviour includes code from the parser library. A correct incremental build must follow that dependency.

## Read the source

[Open the example source](../../../../labs/native/bounded-ledger-line/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Keep source and build directories separate](03-separate-source-and-build.md) · [Next: Understand PUBLIC and PRIVATE usage requirements](05-public-private-usage.md)
