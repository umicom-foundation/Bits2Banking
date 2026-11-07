<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/15-transactional-command-edits.md

PURPOSE:
Keep the previous plan when a command edit is invalid

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep the previous plan when a command edit is invalid

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

## Separate preparation from publication

Suppose a developer changes a valid task to an unfinished command:

~~~text
compiler "unfinished
~~~

The opening quotation mark has no closing partner. A useful parser reports the problem while preserving the previous valid plan. Otherwise a failed edit could leave a mixture of old and new values.

**Failure atomicity** means that a failed operation leaves the promised state unchanged. It does not mean that the operation is automatically thread-safe. Threads are independent execution paths; concurrent access needs its own synchronization rules.

## Read the implementation's ownership

The parser creates a local structure called **staged**. It fills this temporary result while checking the input. Only after every check succeeds does it assign that structure to the caller's output. No pointer to the local structure escapes the function.

This is a small transaction:

~~~text
Read input → prepare temporary result → validate → publish complete result
                                       |
                                       └→ error: keep caller's result
~~~

## Examine the lab's second half

1. Find **previous**, a byte array large enough to hold the command structure.
2. **memcpy** copies the current result into it. The lab saves bytes because it wants to detect any change, including metadata.
3. Parse **unfinished** into the same output variable.
4. Check that the returned status is **UMI_STATUS_PARSE_ERROR**.
5. **memcmp** compares the saved bytes with the current result. A return value of zero means the bytes match.

These byte comparisons are suitable for checking that the same object was untouched. They are not a general way to compare two independently constructed C structures, which may contain padding bytes with no semantic meaning.

## Preserve behaviour above the parser

Task and launch planning must also avoid submitting an operation after parsing fails. The Framework tests inspect the pipeline and check that no operation with the rejected task's ID exists.

A GUI can then keep a draft visible, highlight the invalid command and let the developer correct it. The parser alone does not display that GUI or repair an unrelated click-dispatch problem.

## Practice

Change the lab's rejected text to a valid command and predict why the rejection check fails. Restore the unfinished quote afterwards. This deliberately failing experiment teaches the difference between a successful replacement and preservation after an error.

## Read the source

[Open the example source](../../../../labs/framework/command-arguments/main.c).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Give a parser the exact bytes it may read](14-readable-spans-and-terminators.md) · [Next: Understand the task grammar and the shell boundary](16-task-grammar-and-shell-boundaries.md)
