<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/08-record-build-identity.md

PURPOSE:
Record enough evidence to understand a build result

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Record enough evidence to understand a build result

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


## Evidence has a scope

A useful build record tells a reader what was examined. “Passed” without source identity, command and environment is not enough to compare results later. A Git commit identifies committed content, but uncommitted files may change what a compiler actually reads.

## Make a small record

1. In the repository, run `git status --short --branch` and `git rev-parse HEAD`. These read state; they do not publish changes.
2. Record `cmake --version`, `ninja --version` and `gcc --version`.
3. Record the exact source and build directories and the value of `LESSON_SHOW_HEADING`.
4. Save configure, build and test output in separate files under a timestamped log directory that you choose. In PowerShell use `Tee-Object`; in Bash use `tee`. Check the native command's exit status rather than assuming that writing a log proves success.
5. Record which tests passed, failed or skipped. Keep the original log when you later repair a failure.

## Reading the existing evidence lab

Open `labs/native/build-evidence/evidence.h`. A header declares the data and operations exposed to callers. Find the record fields and compare them with your handwritten record. The teaching lab explores representing evidence in C; it is not a replacement for the repository's authoritative qualification workflow.

## Why exact paths matter

Two Framework checkouts can have different revisions. A parent repository can also record an older submodule commit than the child currently checked out. A report should distinguish the parent identity from the source actually compiled. Do not conclude that every checkout matches because one push succeeded.

## Check your record

Could another learner reproduce the command without guessing the working directory? Could they tell whether the file was changed after the test? Could they distinguish a build failure from a test assertion failure? Add missing facts before making a comparison chart.

Keep credentials and private application data out of shared logs. Diagnostic evidence should be sufficient to explain the failure without becoming an accidental copy of someone's work or account information.


## Read the source

[Open the example source](../../../../labs/native/build-evidence/evidence.h).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Separate failed-test retries from affected-test selection](07-test-selection.md) · [Next: Use an SDK without rebuilding its source in every application](09-sdk-boundaries.md)
