<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/14-readable-spans-and-terminators.md

PURPOSE:
Give a parser the exact bytes it may read

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Give a parser the exact bytes it may read

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

## What a string stores

A C string normally ends with a zero byte, written **'\0'** in C. That byte marks the end; it is not the digit zero. A function such as **strlen** finds the end by reading until that marker. It is safe only when a readable terminator exists.

A **span** describes a sequence with a starting address and a length. Framework's **parse_n** function receives exactly that pair. Its length excludes the terminating byte.

~~~c
static const char text[] = "compiler -c main.c";
UmiDeveloperCommandLine command = {0};
UmiStatus status = umi_developer_command_line_parse_n(
    text, sizeof(text) - 1U, &command);
~~~

**sizeof(text)** is the size of this array, including its automatically added terminator. Subtracting one gives the data length. This calculation works here because **text** is an array in the same scope. Applying **sizeof** to a pointer gives the pointer's size, not the length of the text it points to.

## Trace a bounded read

1. Open the public parser header.
2. Read its promise: the caller supplies readable bytes for the stated length.
3. Open the implementation and find **index < text_length**.
4. Find the backslash look-ahead. It reads the following byte only when that position is inside the span.
5. Find the embedded-zero check. A zero inside the declared span is rejected instead of hiding the bytes after it.

A length is not proof that memory exists. Passing a length larger than the actual readable buffer still violates the caller's contract. This API gives the parser a boundary it can respect; the caller must establish that boundary correctly.

## Fixed fields in saved project data

A project task stores its command in a fixed-size character array. Before reading it as text, the planner uses **memchr** to search for a zero within that array. The difference between the found address and the start is the length. If no zero exists in the field, the planner rejects the record.

That distinction matters when reading corrupted files or data from another component: a field's capacity is not automatically the length of valid text.

## Small exercise

For an array containing the four letters **tool** with no terminator, a span of four bytes can be parsed. For an array containing **tool**, then a zero, then another letter, a span covering all six bytes is rejected. Explain why silently stopping at the zero would conceal part of the declared input.

The older NUL-terminated parser remains available for callers with a valid C string. Use the span interface for buffers whose readable length you already know.

## Read the source

[Open the example source](../../../../../Umicom-Applications/framework/include/umicom/developer/command_line.h).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Pass a program its arguments without losing their boundaries](13-programs-and-argument-boundaries.md) · [Next: Keep the previous plan when a command edit is invalid](15-transactional-command-edits.md)
