<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/12-design-a-build-service.md

PURPOSE:
Connect an IDE to one shared build service

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Connect an IDE to one shared build service

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


## From button to result

An IDE is a user interface for development workflows. A Build button should request work from a service that understands the project, toolchain and dependency state. Reimplementing that reasoning separately in every button makes results inconsistent.

## Trace the boundary

1. Open Framework's build header linked below. Identify the types and public operations before reading their implementation.
2. Search the corresponding `src/toolchain` files for those operations. Find where inputs are validated and where an external process is started.
3. Write the stages in plain language: collect project identity, choose configuration, plan work, execute jobs, collect diagnostics, record evidence.
4. Identify which stages can fail before a compiler starts. A missing project or invalid launch path needs a useful message, not an indefinitely disabled button.
5. Compare this design with the tiny lab: CMake owns the graph, Ninja owns job execution, and CTest owns test invocation. A shared service coordinates existing tools rather than replacing their dependency model with guesses.

## Design an observable interaction

The UI should show the selected project and whether work is queued, running, cancelled, failed or finished. Cancellation is a request; the interface must wait for the worker's result before reusing its state. A completed process with an error code is not a successful build. Keep diagnostic locations so a learner can open the relevant file.

## A regression scenario

Describe a test that opens a small project, requests a build, observes one terminal result, changes one source file and requests another build. The test should inspect actual artifacts and results. Merely confirming that a button callback was registered does not prove that the workflow works.

## Extend responsibly

Add project-specific recipes through the shared contracts. A VHDL simulation, Umicom C preview and native C desktop program have different launch requirements. Studio can present them consistently while keeping their commands explicit. This lesson is a source walkthrough and design exercise; it does not claim every Studio workflow has already passed native UI qualification.


## Read the source

[Open the example source](../../../../../Umicom-Applications/framework/include/umicom/toolchain/build.h).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Compare builds as controlled experiments](11-reproducible-experiments.md)
