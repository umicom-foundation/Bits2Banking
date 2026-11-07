# Introduction to Programming

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## First instructions and results

Use source files, values, decisions, loops and functions to describe small computations.

1. [Instructions, source files and results](01-instructions-source-and-results.md)
1. [Values, variables and decisions](02-values-and-decisions.md)
1. [Repeat work and name a reusable operation](03-loops-and-functions.md)
1. [Describe a result, test it and investigate a failure](04-tests-and-debugging.md)

## Arrays and separate files

Pass lengths explicitly and connect reusable source files into one programme.

1. [Visit values in an array](05-visit-values-in-an-array.md)
1. [Pass an array with its length](06-pass-an-array-with-its-length.md)
1. [Connect source files at link time](07-connect-source-files-at-link-time.md)
1. [Observe output and completion](08-observe-output-and-completion.md)

## Project: a deadline model

Name results, draw states and compare an operation with an independent expected result.

1. [Give results meaningful names](09-name-results-with-an-enumeration.md)
1. [Model a clock with one explicit value](10-model-a-clock-with-a-record.md)
1. [Draw the states an operation can occupy](11-draw-a-state-machine.md)
1. [Test a boundary from both sides](12-check-before-at-and-after.md)
1. [Separate observing state from changing it](13-separate-a-query-from-a-command.md)
1. [Give a special value an explicit meaning](14-give-zero-an-explicit-meaning.md)
1. [Define who wins at a deadline](15-define-cancellation-at-a-deadline.md)
1. [Choose an independent expected result](16-use-an-oracle-for-a-small-model.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/index.md

PURPOSE:
Introduce a course, its prerequisites, tool setup and ordered lessons.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Introduction to Programming

## About this course
Understand instructions, values, decisions, repetition and functions through small C programs. Start with no programming experience.

## Before you begin
No prior programming course is required. You will learn how to open a terminal, read a source file and run a program.

## Reading order
1. [Instructions, source files and results](01-instructions-source-and-results.md)
2. [Values, variables and decisions](02-values-and-decisions.md)
3. [Repeat work and name a reusable operation](03-loops-and-functions.md)
4. [Describe a result, test it and investigate a failure](04-tests-and-debugging.md)


## Prepare a development environment
A compiler translates C source. CMake describes which files belong to a program. Ninja performs the build work. CTest runs registered checks. An editor changes the source text. You may use a plain text editor before learning an IDE.

### Windows with PowerShell
1. Install MSYS2 from [its official installation guide](https://www.msys2.org/). Use the UCRT64 environment described in [the environment guide](https://www.msys2.org/docs/environments/).
2. In the MSYS2 UCRT64 terminal, follow its update instructions, then install the C tools:
~~~bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja git
~~~
3. Obtain the Bits2Banking repository. If it is already present, use that checkout; do not clone into it again. In the MSYS2 terminal, an example new location is:
~~~bash
mkdir -p /c/umicom
git clone https://github.com/umicom-foundation/Bits2Banking.git /c/umicom/Umicom-Bits2Banking
~~~
4. Open PowerShell and add the tools to that terminal's PATH. PATH is the list of directories searched for commands.
~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
~~~
5. Read the files under labs/native/first-c-programs. Run one command at a time and stop on an error. Check $LASTEXITCODE immediately after a native command; zero reports success.
~~~powershell
cmake -S labs/native/first-c-programs -B build/programming-foundations -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/programming-foundations --parallel 2
ctest --test-dir build/programming-foundations --output-on-failure --no-tests=error
& ".\build\programming-foundations\btb-first-hello.exe"
~~~

### Linux with Bash
1. Install Git, a C compiler with the required C23 mode, CMake 3.24 or newer, and Ninja using your distribution's documented package manager. Package names and compiler versions vary.
2. Clone into a new folder if needed:
~~~bash
mkdir -p "$HOME/umicom"
cd "$HOME/umicom"
git clone https://github.com/umicom-foundation/Bits2Banking.git Umicom-Bits2Banking
cd Umicom-Bits2Banking
~~~
3. Check cc --version, cmake --version and ninja --version. If you choose a different compiler, configure a new build directory with -DCMAKE_C_COMPILER set to that compiler.
4. Run each command separately and stop on a failure. echo $? immediately afterwards displays the previous result.
~~~bash
cmake -S labs/native/first-c-programs -B build/programming-foundations -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/programming-foundations --parallel 2
ctest --test-dir build/programming-foundations --output-on-failure --no-tests=error
./build/programming-foundations/btb-first-hello
~~~

## Understand the result
The greeting example prints Hello from Bits2Banking. The accompanying checks compare program output and count-function boundaries. The individual lessons introduce one idea at a time.
The -S argument selects source; -B selects a separate build directory. Building again in that same directory normally updates changed inputs and their dependencies. Testing is a separate step. A successful compile does not establish that the tests or a user workflow passed.

## If setup fails
A missing command means its tool is not installed or not on PATH. A compiler-mode error means you need a compiler that supports the requested C mode. A missing build.ninja file means configuration did not finish successfully. Read the first diagnostic before repeating later commands. Keep source separate from generated build files.

For a slower explanation, use [Learning C](../../learning-c/index.md). The [CMake command manual](https://cmake.org/cmake/help/latest/manual/cmake.1.html) explains configuration and build options.


## What to practise next
Continue with [Learning Data Structures](../learning-data-structures/index.md), then [Learning Algorithms](../learning-algorithms/index.md). [Learning C](../../learning-c/index.md) offers a deeper language sequence.

## Scope
These are introductory chapters and practical labs. Further topics remain to be developed. Successful reading or compilation alone does not establish runtime correctness; compare expected results with your own checks.

- [Visit values in an array](05-visit-values-in-an-array.md)

- [Pass an array with its length](06-pass-an-array-with-its-length.md)

- [Connect source files at link time](07-connect-source-files-at-link-time.md)

- [Observe output and completion](08-observe-output-and-completion.md)

- [Give results meaningful names](09-name-results-with-an-enumeration.md)

- [Model a clock with one explicit value](10-model-a-clock-with-a-record.md)

- [Draw the states an operation can occupy](11-draw-a-state-machine.md)

- [Test a boundary from both sides](12-check-before-at-and-after.md)

- [Separate observing state from changing it](13-separate-a-query-from-a-command.md)

- [Give a special value an explicit meaning](14-give-zero-an-explicit-meaning.md)

- [Define who wins at a deadline](15-define-cancellation-at-a-deadline.md)

- [Choose an independent expected result](16-use-an-oracle-for-a-small-model.md)

</details>
