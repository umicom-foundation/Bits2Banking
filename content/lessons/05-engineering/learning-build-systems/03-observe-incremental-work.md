<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/03-observe-incremental-work.md

PURPOSE:
Observe incremental work before changing the build

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Observe incremental work before changing the build

A build system records how source files become programs and when work must be repeated. This course begins with a small existing Notes library and follows dependencies, generated configuration, tests and evidence into the shared Umicom build architecture.

## Start here

A terminal is a window that accepts commands. A directory is a folder. This course uses a small teaching project in the Bits2Banking checkout; it does not rebuild the complete Framework. You need a C23 compiler, CMake 3.26 or newer, and Ninja. On Windows, open the installed MSYS2 UCRT64 terminal and install the packages below if they are missing:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

Close that terminal and open PowerShell. Adjust the checkout path if yours is elsewhere:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S "labs/native/build-dependency-graph" -B "build/dependency-graph" -G Ninja -DBUILD_TESTING=ON
cmake --build "build/dependency-graph" --parallel 2
ctest --test-dir "build/dependency-graph" --output-on-failure --no-tests=error
```

Run each command separately and stop if it reports an error. For a Linux Bash terminal with GCC, CMake and Ninja installed, change to the Bits2Banking checkout with `cd`, then use the same three `cmake`/`ctest` commands. These are learner exercises; the guide does not assert that a particular machine has passed them. See [Learning CMake](../../../courses/learning-cmake/index.html) for a longer setup and command walkthrough.

Package names can be checked in the official [MSYS2 GCC](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-gcc), [CMake](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-cmake) and [Ninja](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-ninja) listings.


## What incremental means

An incremental build reuses outputs that the build system considers current. It does not promise that one edited source file always means exactly one compiler command. A changed library may trigger several links; a widely used header may trigger many compilations.

## Record a baseline

1. Complete the setup build once.
2. Run `cmake --build build/dependency-graph --parallel 2` again without editing anything. Ninja should normally report no work. If it does work, save the output before changing the project.
3. Ask Ninja to explain its decisions without executing jobs:

```powershell
ninja -C "build/dependency-graph" -n -d explain
```

The same command works in Bash. `-C` selects the build folder. `-n` requests a dry run. `-d explain` prints why outputs are considered dirty, meaning potentially out of date.

4. Add a temporary explanatory comment to `capacity.c`, save it, and repeat the dry run. A normal timestamp-based build can compile this file again even though the comment does not alter its behaviour.
5. Build and run the capacity program. Its output should remain the same. Remove only your experimental comment when finished; do not overwrite unrelated edits.

## Read the evidence

A compiler command includes more than a file name: language mode, include paths, definitions and optimisation settings also matter. Changing such a command can invalidate an object even if the source text is unchanged. Header dependency files tell Ninja about includes discovered by the compiler.

## Connection to Umicom

Framework has additional freshness and public-contract checks. Those checks can deliberately invalidate a broader set of work than this small project. Compare the actual owner build's dirty reasons and source identity before promising the same timings. A fast build of this lab is evidence about this lab alone.

## Troubleshooting

Do not edit `build.ninja` to suppress an unwanted rebuild. It is generated output and a later CMake run can replace it. Find the source description or input whose state changed. If a build repeatedly regenerates the same file, investigate its producing command and whether it rewrites equal content every time.


## Read the source

[Open the example source](../../../../labs/native/build-dependency-graph/capacity.c).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Read a build as a graph of dependencies](02-dependency-graph.md) · [Next: Understand content changes and timestamp limits](04-content-and-timestamps.md)
