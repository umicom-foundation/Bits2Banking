<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/17-command-planning-regression-lab.md

PURPOSE:
Investigate command failures through focused regression checks

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Investigate command failures through focused regression checks

A build button must translate a developer's request into a precise program and a list of arguments. This module follows that translation through Umicom Framework, using a small C exercise to examine spaces, quotation marks, empty arguments and rejected edits.

## Prepare the exercise

A terminal is a window that accepts typed commands. A compiler translates C source into an executable program. CMake describes the build, Ninja carries out the build steps, and CTest runs the checks registered by that build. An SDK supplies the headers and compiled libraries that a program uses.

Reading requires no installation. For the practical work, use a C23 compiler, CMake 3.26 or newer, Ninja, and a matching Umicom Framework SDK that exports the developer component and the exact-span command parser. Use the same architecture and compiler family as the SDK.

1. Find the Bits2Banking checkout and open its **labs/framework/command-arguments** folder.
2. Open PowerShell on Windows or Bash on Linux.
3. Run one command at a time. Stop and read the message if a command fails.
4. Replace the example paths with the locations you chose for the checkout and SDK.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\command-arguments"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
& ".\build\btb-command-arguments.exe"
~~~

~~~bash
cd ~/umicom/Umicom-Bits2Banking/labs/framework/command-arguments
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
./build/btb-command-arguments
~~~

If CMake cannot find UmicomFramework, check the SDK prefix. If the compiler cannot find the parser declaration, or the linker cannot find its symbol, select one SDK containing the new header and its matching library. Do not combine files from different SDK installations. This exercise prints a plan; it does not start a compiler or execute text entered by a user.

For a longer introduction to functions and strings, see [Learning C](../../../courses/learning-c/index.html). The concepts needed for this exercise are explained below.

## What a regression check protects

A regression is the return of behaviour that was previously corrected. A test expresses an observable requirement so that a future change can be compared against it. It cannot guarantee that all possible defects have been found.

The command parser's requirements include preserving empty arguments, respecting readable spans and leaving output unchanged on errors. Each requirement needs a case that would fail if the behaviour were broken.

## Trace the tests

1. Open **test_developer_command_spans.c**.
2. Read **empty_and_joined_arguments**. It checks both an empty token and adjacent quoted fragments.
3. Read **exact_span_and_embedded_zero**. The input is an array of bytes rather than an automatically terminated string.
4. Read the two capacity checks. They exercise the largest accepted program/argument and the first rejected size.
5. Read **overlapping_input_and_output**. It stores the input inside the output object to verify that staging prevents early overwrite.
6. Open the task and launch planner tests. They check the same requirement after translation into a queued operation.

The test source includes the Framework assertion support before the standard assertion header so that required test checks are retained in the project's optimized-build configuration. In ordinary application code, never depend on an assertion to perform required work.

## Build only the relevant test executables

With an already configured Windows Applications build and compatible Framework source, use:

~~~powershell
Set-Location "C:\umicom\Umicom-Applications"
cmake --build --preset windows-ucrt64-all-debug --target umicom-developer-command-spans-tests umicom-developer-task-plan-tests umicom-developer-launch-plan-tests --parallel 2
ctest --test-dir build/windows-ucrt64-all-debug -R "^framework\.developer\.(command_spans|task_plan|launch_plan)$" --output-on-failure --no-tests=error
~~~

These commands are instructions to run the checks, not a claim that they have passed. If the new target is unknown, configure the build using that repository's current setup instructions before retrying.

## Record useful evidence

Write down the source revision, local modifications, compiler, selected targets, command and result. A passing parser test establishes parsing behaviour for that build. A passing planner test adds evidence about operation construction. Neither proves that an IDE window accepts mouse input or that a compiler process successfully starts.

For the complete user workflow, also open a project with a space in its path, edit a file, save it, build it, inspect diagnostics and run its executable. Record each outcome separately so that a failure can be traced to the correct boundary.

## Finish the exercise

Explain the defect in one sentence: token presence was confused with token length. Explain the repair in one sentence: keep a separate started flag and publish only a validated complete plan. Those two sentences identify the cause and the prevention rule without relying on a test count.

## Read the source

[Open the example source](../../../../../Umicom-Applications/framework/tests/test_developer_command_spans.c).

<!-- Earlier end-of-course navigation is retained for comparison; the active route now continues into shared toolchain selection.
## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Understand the task grammar and the shell boundary](16-task-grammar-and-shell-boundaries.md)

-->
## Continue learning

[Next: Distinguish a stored profile from a usable compiler](18-profile-storage-and-tool-usability.md)

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Understand the task grammar and the shell boundary](16-task-grammar-and-shell-boundaries.md)
