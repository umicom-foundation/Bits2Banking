<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/06-register-meaningful-tests.md

PURPOSE:
Register tests that check observable behaviour

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Register tests that check observable behaviour

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


## What a test does

A test performs an operation and compares the outcome with an expectation. CTest starts programs and reports results; the program's assertions specify correctness.

Open test_ledger_line.c and locate one accepted message and one refusal. Read the expected status and row. The mutation program exercises many changed inputs; named cases explain individual boundaries.

~~~powershell
ctest --test-dir build/ledger-line -N
ctest --test-dir build/ledger-line -R "^bits2banking[.]ledger_line[.]syntax$" --output-on-failure --no-tests=error
~~~

-N lists tests without executing them. -R selects names with a regular expression. ^ and $ require the whole name to match. --no-tests=error refuses an empty selection.

## Create an informative failure

1. In a practice copy change one expected value in the test.
2. Rebuild that test program.
3. Run the selected entry and read the assertion location.
4. Restore the correct expectation.
5. Rebuild and rerun.

In product development, an expectation comes from the intended contract. Changing it merely to match a broken implementation hides the defect.

CTest normally runs existing binaries. Editing source and running tests without rebuilding can exercise old code. Record the source revision and successful build before interpreting a pass.

## Distinguish outcomes

A failed assertion differs from a missing executable. A skipped test did not exercise its intended behaviour. An empty selection exercised nothing. Keep these outcomes separate.

## Checkpoint

Why is checking only that an executable exists insufficient? Its existence says nothing about overflow handling, grammar or preservation of output after refusal. Name two observable requirements before adding another test.

## Read the source

[Open the example source](../../../../labs/native/bounded-ledger-line/test_ledger_line.c).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Previous: Understand PUBLIC and PRIVATE usage requirements](05-public-private-usage.md) · [Next: Observe which files an incremental build rebuilds](07-incremental-builds.md)
