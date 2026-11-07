<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/10-use-framework-package.md

PURPOSE:
Use an installed Framework library from a small project

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Use an installed Framework library from a small project

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


## What a package provides

A software package can contain headers, compiled libraries and CMake files describing how consumers use them. An imported target represents a library built elsewhere. The Framework checksum lab demonstrates this boundary with Umicom::base.

This chapter requires an installed Framework SDK that contains the base component. Reading the source needs no SDK. If the SDK is unavailable, keep the practical step pending instead of replacing it with a different library.

## Read the real project

Open labs/native/framework-checksum/CMakeLists.txt and locate:

~~~cmake
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS base)
target_link_libraries(btb-checksum-model PUBLIC Umicom::base)
~~~

find_package searches for a package configuration. CONFIG selects that form of discovery. REQUIRED makes absence a configuration error. COMPONENTS base requests the documented component. The imported target carries usage information supplied by the installed SDK.

## Configure against your installation

In PowerShell at the Bits2Banking repository root, replace the prefix with your actual SDK installation:

~~~powershell
cmake -S labs/native/framework-checksum -B build/framework-checksum -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build build/framework-checksum
ctest --test-dir build/framework-checksum --output-on-failure --no-tests=error
~~~

In Bash the same command structure applies; use your platform's installation prefix. A Windows archive cannot be assumed usable by a Linux compiler.

## Follow the service boundary

BtbChecksumStream reads bytes from a caller-owned FILE stream and calls Framework's SHA-256 service. The lab does not implement SHA-256 again. Its wrapper owns the reading policy and publishes a digest only after successful completion. The caller still closes the stream.

## Diagnose a missing package

Check that the prefix contains lib/cmake/UmicomFramework and that the requested component was installed. A prefix is the installation root, not the path to a single header. Do not add random global include or library directories until the error disappears; identify which package and architecture the compiler uses.

## Exercise and limits

Explain why compiling this consumer does not need to rebuild all Framework sources. Then explain why a checksum alone does not authenticate a download. It detects a difference only against a trusted expected digest; an attacker able to replace both file and digest defeats that comparison.

## Read the source

[Open the example source](../../../../labs/native/framework-checksum/checksum.c).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Locate a failure in configuration, compilation or linking](09-diagnose-build-stages.md) · [Next: Give generated files one owner and complete dependencies](11-generate-files-once.md)
