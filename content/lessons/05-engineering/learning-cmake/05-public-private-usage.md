<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/05-public-private-usage.md

PURPOSE:
Understand PUBLIC and PRIVATE usage requirements

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand PUBLIC and PRIVATE usage requirements

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


## Begin with a header

ledger_line.h declares BtbLedgerLineParse. main.c includes it so the compiler knows the function's inputs and result. The compiler needs a directory in which to find that header.

target_include_directories(btb_ledger_line PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}") applies the directory to the library and its linked consumers. PRIVATE would apply only to the library itself. INTERFACE would apply only to consumers.

The demo links the library PRIVATE because the executable uses the library internally; it does not publish a library interface for other targets.

## Trace the information

1. Find the include in main.c.
2. Find the library's PUBLIC include directory.
3. Find the demo's link to the library.
4. Draw an arrow showing the include requirement travelling with that link.
5. Repeat for the test program.

## Controlled experiment

In a practice copy move the public header into an include subfolder and update the library's PUBLIC include directory. Reconfigure and build all three programs. Each consumer should receive the directory through the target link.

If only the library compiles, check whether the path was incorrectly made PRIVATE. If unrelated targets receive directories they never use, inspect directory-wide settings.

## Framework connection

The framework-checksum lab links Umicom::base. This imported target describes an installed Framework component. Its package supplies include and link requirements. Copying headers into a consumer does not supply the corresponding compiled implementations.

## Question

If a public header uses a type from another library, do consumers need that dependency's include requirements? Usually yes: they must compile the header. Decide from the interface rather than making every dependency PUBLIC by habit.

## Read the source

[Open the example source](../../../../labs/native/framework-checksum/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Build a target and its required dependencies](04-target-dependencies.md) · [Next: Register tests that check observable behaviour](06-register-meaningful-tests.md)
