<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/11-reproducible-experiments.md

PURPOSE:
Compare builds as controlled experiments

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Compare builds as controlled experiments

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


## Repeatable questions

A controlled experiment changes one factor while recording the others. Build performance and reproducibility both benefit from this discipline. “Reproducible” can mean identical output bytes under stated conditions; “same visible behaviour” is a different claim.

## Compare two configurations

1. Configure the lab into `build/dependency-heading` with the heading enabled and `build/dependency-plain` with it disabled. Keep the source directory the same.
2. Build each directory separately and run its registered tests.
3. Run both previews. Explain the intended output difference using the generated header.
4. Compare the capacity programs' visible output. Equal output does not by itself establish byte-identical executables.
5. Record compiler version and options before comparing hashes or timings.

## Sources of variation

Debug information may include paths. Tool versions, timestamps embedded by tools, environment settings and library versions can change outputs. Concurrent work can change elapsed time without changing program content. Some programs intentionally use random values; controlled tests need a documented seed or a property that remains true across seeds.

## What the test actually proves

`check_preview.cmake` starts one executable, checks that it exits successfully and compares its text against the configured expectation. It normalises the Windows newline sequence for the comparison. It does not strip arbitrary whitespace or ignore unexpected lines, because those changes could hide a real output regression.

## Exercise

Write three separate conclusions: the output is correct, the executable hash matches, and this build is faster. State the evidence needed for each. Do not use one measurement as proof of all three.

This applies to LLM lessons too. A fixed training seed, dataset identity and batch plan make an experiment easier to interpret. A model improving on one example is not the same as a validated model release. Build evidence and model evidence share the need for explicitly scoped claims.


## Read the source

[Open the example source](../../../../labs/native/build-dependency-graph/check_preview.cmake).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Distinguish the computer building a program from its target](10-host-and-target.md) · [Next: Connect an IDE to one shared build service](12-design-a-build-service.md)
