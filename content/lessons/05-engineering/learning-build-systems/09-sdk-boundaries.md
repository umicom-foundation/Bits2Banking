<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/09-sdk-boundaries.md

PURPOSE:
Use an SDK without rebuilding its source in every application

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Use an SDK without rebuilding its source in every application

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


## What an SDK contains

A software development kit supplies declarations, libraries and build metadata for another program to consume. Headers explain what callers may use. Libraries provide implementations. A package configuration tells a build system where compatible targets and their required dependencies can be found.

## Trace an existing consumer

1. Open the Framework checksum lab's `CMakeLists.txt` linked below. Locate `find_package` and the imported target used in `target_link_libraries`.
2. Read the checksum source. Identify the Framework function call and the caller-owned input bytes.
3. Locate the installed SDK path on your computer. Do not substitute a source directory for an installation unless that package explicitly supports it.
4. Follow that lab's README to configure a separate consumer build. The small dependency-graph lab in this course does not require an SDK, so finish its basic setup first if the SDK is unavailable.
5. Record the installed package identity alongside the consumer result.

## What changes after an SDK update

An application's own source may be unchanged while its library dependency changes. Relinking may be necessary. If public headers or compile options changed, recompilation can also be necessary. If runtime libraries are loaded dynamically, launching an old executable may load a new library, so a previously recorded pass cannot automatically be reused.

## Architectural lesson

A thin Umicom application selects product workflows and presentation. Framework owns reusable behaviour. An SDK boundary helps enforce that separation only when dependencies are declared accurately. Copying Framework source into the application gives two owners and makes future updates harder to reason about.

## Diagnose carefully

“Package not found” belongs to discovery/configuration. “Undefined reference” belongs to linking. A runtime load failure happens after an executable exists. Check architecture, configuration and installed component availability at the appropriate stage. Do not add random include paths until a compiler happens to accept the build; that can combine incompatible versions.

The official [target linking documentation](https://cmake.org/cmake/help/latest/command/target_link_libraries.html) describes how usage requirements propagate between CMake targets. The local lab shows the concrete target names used by this checkout.


## Read the source

[Open the example source](../../../../labs/native/framework-checksum/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Record enough evidence to understand a build result](08-record-build-identity.md) · [Next: Distinguish the computer building a program from its target](10-host-and-target.md)
