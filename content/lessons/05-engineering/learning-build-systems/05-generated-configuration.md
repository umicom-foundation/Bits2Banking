<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/05-generated-configuration.md

PURPOSE:
Give generated configuration one owner

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Give generated configuration one owner

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


## What generation does

A generated file is produced by a tool from other inputs. In this lab CMake turns `lesson_config.h.in` into `generated/lesson_config.h` inside the selected build folder. The template asks for a value of zero or one for `LESSON_SHOW_HEADING`.

## Change a setting

1. Build and run the default preview. Its first line should be `Umicom Notes preview`.
2. Configure the same build with the option disabled:

```powershell
cmake -S "labs/native/build-dependency-graph" -B "build/dependency-graph" -DLESSON_SHOW_HEADING=OFF
ninja -C "build/dependency-graph" -n -d explain
cmake --build "build/dependency-graph" --parallel 2
ctest --test-dir "build/dependency-graph" --output-on-failure --no-tests=error
```

3. Run the preview. Only the note text should be printed. The test receives the same configured option and compares the expected output.
4. Inspect the generated header. It contains an ordinary `#define`, not a runtime variable. The preprocessor selects the branch when compiling.
5. Return the option to `ON` with the first command and rebuild when you want the original heading.

## Why ownership matters

Both executables may consume a shared output, but that does not give both targets permission to define a separate producing rule for the same path. Parallel build drivers need a single unambiguous writer. The official [CMake custom-command reference](https://cmake.org/cmake/help/latest/command/add_custom_command.html) explains output ownership and declared byproducts for build-time generation.

Configuration-time generation used here is a different phase from an `add_custom_command` job. Choose the phase according to when inputs are available. In both cases keep outputs in the build tree and record all inputs.

## Recovery

If Ninja reports that a path is defined as output multiple times, search the CMake source for every rule producing that exact path. Remove the duplicate ownership in the design while preserving the required generation through its shared owner. Merely renaming one generated file can hide the symptom while leaving consumers inconsistent.


## Read the source

[Open the example source](../../../../labs/native/build-dependency-graph/lesson_config.h.in).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Understand content changes and timestamp limits](04-content-and-timestamps.md) · [Next: Run independent build jobs in parallel](06-parallel-jobs.md)
