<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/11-generate-files-once.md

PURPOSE:
Give generated files one owner and complete dependencies

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Give generated files one owner and complete dependencies

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


## What is a generated file?

A generated file is produced by another tool: a compiled resource, protocol binding, copied build asset or analysis stamp. The build graph must identify which command produces it. Two independent rules claiming the same output make that graph ambiguous.

A source asset and its staged build copy should have different paths. Configuration should not overwrite an input with a generated copy of itself.

## Read the CPU example

Open labs/hardware/vhdl-cpu/CMakeLists.txt. Its custom command analyses the VHDL sources and elaborates a simulation. After those commands succeed it touches analysis.stamp inside the build directory. The custom target cpu_analysis depends on that stamp. The command declares both VHDL source files and the simulator as dependencies.

~~~text
CPU source + testbench + simulator
                 |
                 v
       analyse and elaborate
                 |
                 v
         analysis.stamp
                 |
                 v
           cpu_analysis
~~~

The stamp records that the declared commands completed; it does not prove every possible CPU behaviour.

## A paper exercise before running anything

1. Find the OUTPUT argument. Identify the single producing rule.
2. Find DEPENDS. Check that both source paths are present.
3. Find the working directory. Explain where simulator files are written.
4. Find VERBATIM. Explain why argument boundaries matter when a project folder contains spaces.
5. Draw a separate arrow from the simulation target to cpu_analysis.

This exercise needs no simulator. For a practical run, follow the VHDL lab README and install a compatible GHDL.

## Diagnose a duplicate-output error

Search the project descriptions for the output path. Check aliases, repeated includes, source-directory writes and two modules staging the same resource. Assign staging to one shared owner and let consumers depend on it. Suppressing the error does not resolve ambiguous ownership.

## When an input changes

A complete dependency list lets the build tool invalidate the stamp. An omitted input may leave stale generated output. A stamp should be written after successful work, never before it, or a failed operation could appear current.

## Review

Why should a packaging target depend on shared resource preparation instead of defining a second copy rule for the same destination? The dependency expresses reuse and preserves one producer for each artifact.

## Read the source

[Open the example source](../../../../labs/hardware/vhdl-cpu/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Use an installed Framework library from a small project](10-use-framework-package.md) · [Next: Keep build results useful for the next developer](12-create-build-evidence.md)
