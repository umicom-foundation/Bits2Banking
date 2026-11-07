<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/06-parallel-jobs.md

PURPOSE:
Run independent build jobs in parallel

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Run independent build jobs in parallel

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


## Jobs and dependencies

A job is one unit of build work, such as compiling a source file. Two jobs can run together if neither needs the other's output. A link must wait for its required objects. Increasing parallelism does not remove this ordering.

## Read before tuning

1. Count independent source compilations in the lab. The preview, capacity and Notes implementation can often compile concurrently.
2. Find the two executable link steps. Each needs its own object and the library.
3. Build with `--parallel 2`. This limits the number of concurrent jobs requested by CMake from the build driver.
4. Compare a later build with a larger value only when the machine has enough memory and you are measuring real work. A no-op build cannot tell you how quickly compilation scales.
5. Record elapsed time, peak memory if available, and the number of jobs. Do not compare different source revisions as if they were the same experiment.

## Why more is sometimes slower

Compilers use memory, CPU time and storage bandwidth. If too many run at once, the operating system may move memory pages to disk or jobs may compete for the same resource. A large link can also dominate the total even when compilation is fast.

A **race** occurs when work depends on timing that has not been made explicit. Two jobs writing the same generated file are an example. Parallel execution often reveals such bugs; forcing one job may only conceal them.

## Build concurrency and test concurrency

Building with several jobs and running several tests together are separate decisions. A GUI test, a test using a shared port, or a test writing one fixture may require isolation. A test is not safe to run concurrently merely because its source compiled in parallel.

## Lab extension

Sketch a third consumer that needs only the Notes header and library. Explain which edges must be added. Do not create another implementation of `UmicomNoteSet`. In Umicom, shared services belong in Framework and application targets declare their dependency on those services.

For an unexpected parallel-only failure, preserve the first failing command and inspect shared outputs before changing scheduling. Repeat measurements only after the dependency model is understood.


## Read the source

[Open the example source](../../../../labs/native/build-dependency-graph/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Give generated configuration one owner](05-generated-configuration.md) · [Next: Separate failed-test retries from affected-test selection](07-test-selection.md)
