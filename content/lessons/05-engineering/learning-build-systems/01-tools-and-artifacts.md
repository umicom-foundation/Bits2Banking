<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/01-tools-and-artifacts.md

PURPOSE:
Meet the tools and the files they produce

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Meet the tools and the files they produce

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


## What you will learn

A build system turns a description of a program into a sequence of jobs. It must know both what to run and when a result needs to be produced again. An **artifact** is an output of a job, such as an object file, library or executable.

## Follow one note

1. Open `preview.c` as text. The line including `notes.h` supplies declarations: it tells the compiler the shape of a note and the name of the function that fills it.
2. Open `../safe-notes/notes.c`. This is the implementation already used by the safer C lessons. The new lab references this file; it does not copy the function.
3. Open `CMakeLists.txt`. `add_library(lesson-notes STATIC ...)` groups that implementation into an archive. An archive is a collection of compiled object files.
4. Find `target_link_libraries(lesson-note-preview PRIVATE lesson-notes)`. This records that the preview needs the library when the linker assembles the program.
5. Build with the setup commands. Then run `& ".\build\dependency-graph\lesson-note-preview.exe"` in PowerShell, or `./build/dependency-graph/lesson-note-preview` in Bash. The expected text is a heading followed by `Trace a build dependency`.

`#include` is handled during preprocessing. Compilation checks and translates C. Assembly encodes machine instructions. Linking resolves references between compiled files. A compiler driver such as GCC can coordinate these stages, but a successful compilation of one source file does not prove that the final link will succeed.

CMake reads the project description and generates build instructions. Ninja executes the resulting jobs. CTest runs named checks after the executable exists. None of these roles should be confused with the application itself.

## Try and explain

Run the capacity program beside the preview. It should report 128 storage bytes and 127 maximum text bytes. Both executables use the same declaration even though their visible output differs. Draw arrows from each executable to the library and from each object to its source.

## If something goes wrong

A missing compiler is a setup failure. An unknown C identifier is a source/declaration failure. An undefined reference is usually detected at linking. Record the first error and the command that produced it; later failures may only be consequences. The exercise is complete when you can identify the failed stage without assuming every failure requires deleting the build directory.


## Read the source

[Open the example source](../../../../labs/native/build-dependency-graph/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Next: Read a build as a graph of dependencies](02-dependency-graph.md)
