<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/16-task-grammar-and-shell-boundaries.md

PURPOSE:
Understand the task grammar and the shell boundary

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand the task grammar and the shell boundary

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

## Two interpreters with different jobs

A **shell** is a command interpreter such as PowerShell or Bash. It can perform operations beyond starting one program: variables, pipelines and redirection are examples. A task parser can instead produce a literal list of arguments without performing those operations.

Framework's compatibility task format groups text with single or double quotes. A backslash escapes another backslash, either quote, or whitespace. Other backslashes are literal, which is useful in ordinary Windows paths. This is the established Framework task grammar; do not assume every PowerShell or Bash quoting rule applies.

## Work through the examples

| Task text | Result |
| --- | --- |
| compiler "source file.c" | One argument containing a space |
| compiler source\ file.c | The escaped space stays in the argument |
| compiler before""after | One argument: beforeafter |
| compiler "a|b" | One literal argument containing a vertical bar |
| compiler a|b | Parse error |
| compiler "$HOME" | Literal dollar sign and letters; no variable expansion |

The quotation marks in this table belong to the task text. When writing that text as a C string literal, escape embedded double quotes for the C compiler.

## A parser is not an authorization system

Rejecting unquoted operators prevents accidental interpretation of task text as a shell expression. It does not make every executable or every argument safe. A task could explicitly name a shell, a downloader or a destructive tool.

Before execution, the application still needs to establish what the user authorized, which executable will run, its working directory, its environment and its permissions. Do not place passwords or access tokens in task text: process arguments and diagnostic logs may expose them.

## Follow the next boundary

1. Open Framework's platform process source.
2. On POSIX hosts, find where argument pointers are assembled into an array ending with a null pointer.
3. On Windows, read **process_windows_arguments.inc**. It quotes the literal arguments for the Windows C runtime convention, including an empty string.
4. Keep parsing separate from encoding for the operating system. Parsing decides what the arguments are; encoding transports those already chosen values.

The platform adapter supports specific process-launch paths. Review the selected path when introducing a new tool, especially a script interpreter. Do not rebuild a shell command by concatenating the parsed strings in application code.

## Check your understanding

Why does a quoted vertical bar not create a pipeline here? It remains data passed to a program. Could that program interpret the data itself? Yes. Each receiving component needs an explicit contract.

## Read the source

[Open the example source](../../../../../Umicom-Applications/framework/src/developer/command_line.c).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Previous: Keep the previous plan when a command edit is invalid](15-transactional-command-edits.md) · [Next: Investigate command failures through focused regression checks](17-command-planning-regression-lab.md)
