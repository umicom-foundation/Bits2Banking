<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/07-incremental-builds.md

PURPOSE:
Observe which files an incremental build rebuilds

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Observe which files an incremental build rebuilds

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


## What incremental means

An incremental build reuses outputs whose recorded inputs have not changed. An object file is the compiler's result for one source file. The linker combines object files and libraries into an executable. Ninja follows a dependency graph: an arrow from an input to an output means that changing the input may require rebuilding that output.

Our lab has one library source, three executable sources and a shared header. That small graph makes the decisions visible.

## Investigate the graph

1. Complete the setup below and build once.
2. Run the same build command again. With unchanged inputs and commands, expect no compilation work.
3. In a personal exercise copy, add a comment to main.c. Save it and run the build with verbose output:

~~~powershell
cmake --build build/ledger-line --verbose
~~~

4. The demo source should compile and the demo executable should link. Changing only this executable's source should not compile the parser or mutation test.
5. Edit ledger_line.h in the exercise copy and build again. Sources that include it may rebuild, even when the edit is only a comment.
6. Restore the exercise content using your editor's undo function and rebuild.

The exact displayed command count depends on generator and toolchain. Explain the input relationship rather than memorising a count.

## Why a comment can trigger work

Most ordinary compiler build rules use file timestamps and recorded header dependencies. They do not prove that a source edit has the same meaning. Compiler definitions, include files, generated files and command options can all affect output. A tool that ignores comments must still preserve diagnostics, line information and preprocessing behaviour. A content cache is a separate optimisation, not permission to omit dependencies.

## Connect this to Studio

A Studio Build command should request the selected project's build graph. It should not invoke a clean operation every time. Framework's developer-project service supplies project identity and build information; the build tool then determines required compilation.

## Check your understanding

If test_ledger_line.c changes, which executable should need a new object? If the parser's public header changes, why can several executables rebuild? The first change belongs to one target; the second changes a shared input.

## When results are surprising

Check timestamps, generated headers and verbose compiler commands. A constantly rewritten generated header can cause repeated work. Do not remove dependency declarations to make a build appear faster.

## Read the source

[Open the example source](../../../../labs/native/bounded-ledger-line/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Register tests that check observable behaviour](06-register-meaningful-tests.md) · [Next: Choose tests using evidence about a change](08-tests-after-a-change.md)
