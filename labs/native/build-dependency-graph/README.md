<!--
Umicom Bits2Banking
File: labs/native/build-dependency-graph/README.md

PURPOSE:
Explain the dependency-graph experiment, setup and expected observations.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Build dependency graph laboratory

This lab reuses `../safe-notes/notes.c` and its tests. It adds two consumers to make dependency relationships visible without introducing another Notes implementation.

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

Run each command separately and stop if it reports an error. For a Linux Bash terminal with GCC, CMake and Ninja installed, change to the Bits2Banking checkout with `cd`, then use the same three `cmake`/`ctest` commands. These are learner exercises; the guide does not assert that a particular machine has passed them. See [Learning CMake](../../../content/courses/learning-cmake/index.html) for a longer setup and command walkthrough.

Package names can be checked in the official [MSYS2 GCC](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-gcc), [CMake](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-cmake) and [Ninja](https://packages.msys2.org/packages/mingw-w64-ucrt-x86_64-ninja) listings.

## File map

| File | Purpose |
|---|---|
| CMakeLists.txt | Defines one Notes library and its two consumers; configures the private header. |
| lesson_config.h.in | Template for the preview-only heading switch. |
| preview.c | Uses the Notes service and the generated header. |
| capacity.c | Observes the public capacity without using the private header. |
| check_preview.cmake | Runs the preview and checks its visible result. |
| ../safe-notes/notes.c | Existing bounded update implementation. |
| ../safe-notes/test_notes.c | Existing boundary and preservation checks. |

## Expected results

Run `lesson-note-preview` from the selected build directory. With the default setting it prints `Umicom Notes preview`, then `Trace a build dependency`. On Windows append `.exe`. `lesson-note-capacity` prints 128 storage bytes and 127 maximum text bytes. These are expected results, not execution evidence.

## Observe the graph

Run `ninja -C build/dependency-graph -n -d explain` from the repository root to inspect pending work. Change only `LESSON_SHOW_HEADING` through CMake, inspect the generated header, then build and test. The capacity source does not consume that header. A public Notes header change has a different dependency reach. Preserve unrelated changes while experimenting.

## Continue learning

[Learning Build Systems](../../../content/courses/learning-build-systems/index.html) follows these files through twelve practical lessons.
