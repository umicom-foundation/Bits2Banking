<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/10-host-and-target.md

PURPOSE:
Distinguish the computer building a program from its target

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Distinguish the computer building a program from its target

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


## Two computers in one build

The **host** is the system running your build tools. The **target** is the system that will execute the produced program. They may be the same computer. A Windows machine compiling a RISC-V kernel is a cross-compilation example: its compiler runs on Windows and emits instructions for a different architecture.

## Begin with the hosted lab

1. Build and run the dependency-graph example using the setup section. It is a hosted program: it uses the C library and the current operating system.
2. Write down your host operating system and processor architecture.
3. Open the Kernel presets linked below as text. Look for the compiler, toolchain and build directory associated with the RISC-V profile. Reading a preset is not booting a kernel.
4. Compare the kernel's target environment with the preview's use of `stdio.h`. A freestanding kernel supplies facilities that a hosted program normally receives from an operating system and runtime.
5. Continue to [Introduction to Operating Systems](../../../courses/introduction-to-operating-systems/index.html) and the Kernel course for the supported emulator workflow before attempting target execution.

## Build-time tools need a host

A program that generates a header during a build must itself run on the host. Accidentally compiling that generator for RISC-V and then trying to execute it on Windows will fail. A toolchain description must keep generated target programs separate from host tools.

## Test identity changes too

A host model test can check arithmetic or a protocol structure without proving that interrupts, devices or boot entry work on target hardware. Emulator evidence and physical-machine evidence should be recorded separately. Reusing a pass across these environments requires a clear contract, not just the same test name.

## Exercise

Draw two boxes labelled host and target. Place CMake, compiler, generator, executable, emulator and test driver in the appropriate box; some relationships cross the boundary. Explain why an IDE's Run button needs an explicit launch recipe rather than assuming that every successful build produces a local desktop executable.


## Read the source

[Open the example source](../../../../../umicom-kernel/CMakePresets.json).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Use an SDK without rebuilding its source in every application](09-sdk-boundaries.md) · [Next: Compare builds as controlled experiments](11-reproducible-experiments.md)
