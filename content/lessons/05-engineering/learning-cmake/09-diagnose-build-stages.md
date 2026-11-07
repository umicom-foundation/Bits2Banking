<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/09-diagnose-build-stages.md

PURPOSE:
Locate a failure in configuration, compilation or linking

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Locate a failure in configuration, compilation or linking

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


## Give each stage a name

Configuration reads the project description and locates required tools. Generation writes instructions for a build tool. Compilation translates a source file into an object. Linking resolves references between objects and libraries. Testing runs programs and checks results. A failure at one stage can prevent later stages from producing trustworthy evidence.

## A controlled investigation

Work only in a personal copy of the bounded-ledger-line lab.

1. Start from a passing build of the unmodified copy.
2. Change the source filename in add_library to a name that does not exist. Configure again. Expect CMake to report a missing source.
3. Undo that edit. Configure successfully.
4. Remove a required semicolon in your copy of main.c. Build. Expect a compiler diagnostic naming a file and line.
5. Undo that edit and rebuild.
6. Examine the target_link_libraries entry for the demo. In a second exercise copy, omit its parser library and give the compiler its existing header path explicitly. The declarations may compile, but a call to the parser has no linked definition.
7. Restore the original project before continuing.

The final experiment separates knowing a function's declaration from supplying its implementation. Do not repair an unresolved function by copying its implementation into every consumer.

## Read the first useful diagnostic

A long build may report many consequences of one shared error. Start with the earliest specific failure, its command and source location. “Subcommand failed” is a summary, not the cause. For an undefined reference, check the function's spelling, whether its source belongs to a target and whether the consumer links that target.

## Preserve comparison evidence

Record the source revision, compiler version, build directory, command and exit status alongside the log. Avoid reusing the same filename for unrelated runs. Never infer that a newly edited source file was used by an older executable.

## Apply this to Umicom

A Framework service belongs in its shared library. Studio and other applications should link the service rather than maintain duplicate fixes. Regression coverage should call the public interface and check behaviour, not merely check that a source file contains a word.

## Review question

Why can an application compile but fail to link? A header can describe a function while no linked object supplies that function's definition.

## Read the source

[Open the example source](../../../../labs/native/bounded-ledger-line/main.c).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Choose tests using evidence about a change](08-tests-after-a-change.md) · [Next: Use an installed Framework library from a small project](10-use-framework-package.md)
