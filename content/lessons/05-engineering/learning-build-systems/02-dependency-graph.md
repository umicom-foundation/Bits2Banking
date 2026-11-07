<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/02-dependency-graph.md

PURPOSE:
Read a build as a graph of dependencies

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read a build as a graph of dependencies

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


## The central idea

A **dependency** is something a result requires. A **graph** is a set of items and connections. Here the items are files and jobs, and a connection means that a job must wait for or observe an input.

```text
notes.c + notes.h  --> notes object --> lesson-notes library
preview.c + notes.h + generated header --> preview object
capacity.c + notes.h                   --> capacity object
preview object + library               --> preview program
capacity object + library              --> capacity program
```

The arrow means “is needed to produce”, not “runs continuously”. The generated header comes from CMake's configuration step. It is private to the preview: the capacity source never includes it.

## Walk the actual files

1. Read the two `#include` lines at the top of `preview.c` and the single local include in `capacity.c`.
2. Find the public include directory on `lesson-notes`. Public usage information reaches consumers so they can find `notes.h`.
3. Find the private generated include directory on `lesson-note-preview`. This keeps a preview detail out of the capacity command.
4. Read `lesson_config.h.in`. It is a template, not directly compiled C. CMake replaces its configuration directive before the compiler sees the generated header.
5. Use `cmake --build build/dependency-graph --target lesson-note-preview --verbose` to inspect real compiler and linker commands. Do not infer dependencies only from the visual folder tree.

## A useful distinction

A header declaration and its implementation have different roles. If the implementation body changes, the library object must be recreated and consumers may need relinking. Their own source objects need not always be compiled again. If the public header changes, every object that included it may need recompilation because declarations, constants or layout can affect generated instructions.

## Exercise

Write a prediction before each edit: which objects, library and programs should become out of date? Compare that prediction with the jobs shown by Ninja. Explain an unexpected job by finding a real command, input or generated configuration difference. Do not remove dependency edges simply to make the displayed job count smaller.

This mirrors Umicom's architecture: applications consume Framework targets and public contracts. A shared library must have one implementation even when several applications depend on it.


## Read the source

[Open the example source](../../../../labs/native/build-dependency-graph/preview.c).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Meet the tools and the files they produce](01-tools-and-artifacts.md) · [Next: Observe incremental work before changing the build](03-observe-incremental-work.md)
