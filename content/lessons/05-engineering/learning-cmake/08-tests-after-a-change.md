<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/08-tests-after-a-change.md

PURPOSE:
Choose tests using evidence about a change

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Choose tests using evidence about a change

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


## Builds and tests answer different questions

A successful build means the selected compilation and link steps completed. A test checks an expected behaviour. CTest does not automatically infer every behaviour affected by a source edit. A selection policy must consider the changed implementation, its consumers and previous failures.

For this lab, changing ledger_line.c can affect every parser test and the demonstration. Changing only a README does not alter those binaries, although documentation examples may still need review.

## Inspect before selecting

1. Configure and build using the setup below.
2. List registered tests without running them:

~~~powershell
ctest --test-dir build/ledger-line -N
~~~

3. Inspect their commands in CMakeLists.txt. Identify the syntax tests, mutation tests and demonstration.
4. Run the complete small lab:

~~~powershell
ctest --test-dir build/ledger-line --output-on-failure --no-tests=error
~~~

5. After investigating a failure and rebuilding its affected targets, use:

~~~powershell
ctest --test-dir build/ledger-line --rerun-failed --output-on-failure
~~~

Rerunning failures is useful confirmation for those tests. It does not cover a previously passing test newly affected by the same fix. Keep the prior failure evidence before a later run changes the current CTest results.

## Plan an affected-test record

For each selected test, record its name, executable, source revision, toolchain, relevant inputs and last result. A cached pass is applicable only to the inputs and environment it identifies. Missing ownership information should widen the selection, not silently count as a pass. Shared public-header changes can affect several applications.

## An exercise in selection

Imagine fixing rejection of embedded zero bytes in BtbLedgerLineParse. Select tests with byte-count inputs, malformed inputs, output-preservation checks and ordinary valid records. A test that merely launches the demo does not exercise all those cases. Write down why each test belongs.

## Troubleshooting

“No tests were found” can mean the wrong build directory or BUILD_TESTING=OFF. It is not a success for a required suite. A missing executable can mean the test target was not built. A timeout needs investigation of the child process and its inputs before increasing a deadline.

## Further reading

The official CTest manual documents selection flags and result files. This course's selection exercise uses the local parser graph; it is not a claim that CTest supplies a complete change-impact engine.

## Read the source

[Open the example source](../../../../labs/native/bounded-ledger-line/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Observe which files an incremental build rebuilds](07-incremental-builds.md) · [Next: Locate a failure in configuration, compilation or linking](09-diagnose-build-stages.md)
