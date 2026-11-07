<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/07-test-selection.md

PURPOSE:
Separate failed-test retries from affected-test selection

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate failed-test retries from affected-test selection

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


## A test is a question

The Notes boundary test asks whether bounded updates preserve their contract. The preview test asks whether a configured program prints the correct visible result. Passing one does not answer the other's question.

A failed-test retry selects tests by the result of a previous run. Affected-test selection selects tests because their relevant inputs changed. These sets can overlap, but they are not identical.

## Try both deliberately

1. Build the complete lab before running tests. CTest does not automatically compile missing executables.
2. List tests with `ctest --test-dir build/dependency-graph -N`. Listing is not executing.
3. Run the whole small suite with the setup command and inspect both names.
4. After a failure and a fix, `ctest --test-dir build/dependency-graph --rerun-failed --output-on-failure` can retry recorded failures. It does not select previously passing tests affected by the same fix.
5. For this lab, run the full two-test suite after changing Notes logic or generated configuration. It is small enough that the relevant contract checks remain clear.

## What a reusable result must describe

Record the test name, executable identity, runtime libraries, fixtures, configuration and outcome. A pass from a different binary is historical evidence, not a current pass. A skipped test and a missing executable must remain distinguishable from success.

## Studio and Framework

A Studio button should ask the shared Framework build/test service for a plan and show why tests were selected. It should not invent a separate cache of successful results. Unknown dependency relationships require a broader plan or an explicit unresolved state. This is especially important for plugins and runtime-loaded resources whose dependencies are not all in a compiler's include list.

## Exercise

Make a table of three changes: heading option, Notes capacity, and test expectation. For each, identify which artifact changes and which test questions must be answered again. Explain why changing an expected value merely to obtain green results is not a repair when the implementation violates its documented behaviour.


## Read the source

[Open the example source](../../../../labs/native/build-dependency-graph/check_preview.cmake).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Run independent build jobs in parallel](06-parallel-jobs.md) · [Next: Record enough evidence to understand a build result](08-record-build-identity.md)
