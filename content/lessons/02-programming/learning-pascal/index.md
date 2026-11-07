# Learning Pascal

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## Values, records and units

Compile a first programme, then group values and share checked functions.

1. [Write and run a Pascal program](01-write-and-run-a-program.md)
1. [Values, functions and input validation](02-values-functions-and-validation.md)
1. [Loops and checkable results](03-loops-and-checkable-results.md)
1. [Group related values in a record](04-group-values-in-records.md)
1. [Share a unit and preserve state on failure](05-share-a-unit-and-preserve-state.md)

## Project: a course notebook

Apply bounded arrays, text validation and reusable units to independent course records.

1. [Build a small course notebook](06-build-a-course-notebook.md)
1. [Distinguish array capacity from occupied entries](07-distinguish-capacity-from-count.md)
1. [Translate a public number into an array index](08-translate-public-course-numbers.md)
1. [Validate a name before bounded storage](09-validate-text-before-storage.md)
1. [Reuse progress arithmetic through a unit](10-reuse-a-unit-through-composition.md)
1. [Preserve caller state when an operation is refused](11-preserve-results-on-refusal.md)
1. [Check that one course cannot change another](12-check-each-course-independently.md)
1. [Design saving before adding file writes](13-design-the-next-persistence-step.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/index.md

PURPOSE:
Introduce a course, its prerequisites, tool setup and ordered lessons.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Learning Pascal

## About this course
Write, compile and check Pascal console programs using values, decisions, functions and loops.

## Before you begin
No knowledge of Pascal or another programming language is assumed.

## Reading order
1. [Write and run a Pascal program](01-write-and-run-a-program.md)
2. [Values, functions and input validation](02-values-functions-and-validation.md)
3. [Loops and checkable results](03-loops-and-checkable-results.md)
4. [Group related values in a record](04-group-values-in-records.md)
5. [Share a unit and preserve state on failure](05-share-a-unit-and-preserve-state.md)


## Install and check the tools
1. Download Free Pascal for your operating system from [the official download page](https://www.freepascal.org/download.html). Follow the installation notes for that package.
2. Open PowerShell on Windows or a terminal on Linux. Type fpc -iV. Expect a compiler version. If the command is missing, locate the installed fpc executable and add its containing bin directory to PATH using the installation instructions. Do not guess another machine's installation path.
3. Obtain Bits2Banking in a folder you choose. With Git installed, a Windows example is:
~~~powershell
New-Item -ItemType Directory -Force "C:\umicom"
Set-Location "C:\umicom"
git clone https://github.com/umicom-foundation/Bits2Banking.git Umicom-Bits2Banking
~~~
Skip cloning if your checkout already exists. The examples live in labs/languages/pascal-progress. Open hello.pas and progress.pas in a plain text editor.

## Compile without another build tool
Make a new practice directory and copy the two Pascal files there. Compile from that directory so object files do not appear beside your learning sources.
~~~powershell
fpc -Mobjfpc -Cr -Co hello.pas
.\hello.exe
fpc -Mobjfpc -Cr -Co progress.pas
.\progress.exe 2
$LASTEXITCODE
~~~
In Bash the compiler commands are identical; launch with ./hello and ./progress 2, then inspect echo $?. Stop if compilation fails. -Cr enables range checks and -Co enables overflow checks. These checks aid diagnosis; they do not prove all program behaviour correct.

Expect Welcome to Learning Pascal. from hello. progress 2 prints Remaining: 3 and three numbered practice lines.

## Build and check the complete lab
Install CMake 3.24 or newer and Ninja for your operating system. They organise the examples and process checks; Free Pascal remains the language compiler. From the Bits2Banking repository in PowerShell:
~~~powershell
cmake -S labs/languages/pascal-progress -B build/pascal-progress -G Ninja -DBUILD_TESTING=ON
cmake --build build/pascal-progress --parallel 2
ctest --test-dir build/pascal-progress --output-on-failure --no-tests=error
& ".\build\pascal-progress\progress.exe" 2
~~~
In Bash:
~~~bash
cmake -S labs/languages/pascal-progress -B build/pascal-progress -G Ninja -DBUILD_TESTING=ON
cmake --build build/pascal-progress --parallel 2
ctest --test-dir build/pascal-progress --output-on-failure --no-tests=error
./build/pascal-progress/progress 2
~~~
Run commands separately. CMake must find fpc on PATH. A failed configuration does not produce a usable build. A test failure needs investigation even when compilation succeeded.

## Reference and recovery
The [Free Pascal manuals](https://www.freepascal.org/docs.html) explain the compiler and language. The [Val documentation](https://www.freepascal.org/docs-html/rtl/system/val.html) defines conversion results and supported numeric formats. Our exercises use decimal counts. A rejected abc input is expected; an unexpected crash is not.

This course uses Pascal to teach Pascal concepts. Shared application engines remain in Umicom Framework. No Pascal runtime is being introduced into those applications.


## What to practise next
Extend the progress program with named practice items after learning arrays. Use the existing examples to keep conversion, validation and presentation separate.

## Scope
These are introductory chapters and practical labs. Further topics remain to be developed. Successful reading or compilation alone does not establish runtime correctness; compare expected results with your own checks.

- [Build a small course notebook](06-build-a-course-notebook.md)

- [Distinguish array capacity from occupied entries](07-distinguish-capacity-from-count.md)

- [Translate a public number into an array index](08-translate-public-course-numbers.md)

- [Validate a name before bounded storage](09-validate-text-before-storage.md)

- [Reuse progress arithmetic through a unit](10-reuse-a-unit-through-composition.md)

- [Preserve caller state when an operation is refused](11-preserve-results-on-refusal.md)

- [Check that one course cannot change another](12-check-each-course-independently.md)

- [Design saving before adding file writes](13-design-the-next-persistence-step.md)

</details>
