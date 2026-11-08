<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/13-programs-and-argument-boundaries.md

PURPOSE:
Pass a program its arguments without losing their boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Pass a program its arguments without losing their boundaries

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

## From a button to a process

A **process** is a running instance of a program. A build request names an executable, such as a compiler, and supplies arguments telling it what to do. The list is often called **argv**, meaning argument vector. Each element is a separate string.

Consider this task text:

~~~text
compiler -c "source file.c" ""
~~~

Its intended result is:

| Part | Value | Meaning in this exercise |
| --- | --- | --- |
| Program | compiler | A name inspected by the lab; no program is launched |
| Argument 1 | -c | One option string |
| Argument 2 | source file.c | One file name containing a space |
| Argument 3 | empty string | A deliberately present positional argument |

Quotation marks group text in this task format. They do not become part of the second argument. The final pair of quotation marks creates an argument with zero characters. An absent argument and an empty argument are different requests: a program can assign a meaning to a position even when its value is empty.

## Follow the C exercise

1. Open **main.c** in the lab folder.
2. Find the declaration of **text**. The C source uses a backslash before each quotation mark that must be stored inside the string.
3. Find **UmiDeveloperCommandLine command = {0}**. A structure groups related values; this structure holds the program, argument strings and argument count. The initializer starts its members at zero.
4. Find **umi_developer_command_line_parse_n**. It reads task text and fills the structure only when the request is valid.
5. Run the exercise and compare the printed boundaries.

~~~text
Program: compiler
Argument 1: [-c]
Argument 2: [source file.c]
Argument 3: []
Rejected edit left the previous plan unchanged.
~~~

Square brackets are added by the lab's print statement to make an empty value visible. They are not part of the argument.

## Why counting characters is insufficient

A parser that records a token only when its length is greater than zero loses the final argument. The next value can then move into the wrong position. Framework tracks two facts separately: whether a token has started and how many bytes it contains.

Try writing the expected argument list for **compiler "" tail** before reading it with a debugger. There are two arguments. The first is empty and the second is **tail**.

## Check your understanding

Why is **source file.c** one argument? The quotation marks group the space with the file name. Why keep the final empty argument? Its position can matter to the receiving program. This exercise verifies parsing; it does not establish that the named compiler accepts those particular arguments.

## Read the source

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/command-arguments/main.c).

## Continue learning

[Course contents](../../../courses/learning-build-systems/index.html) · [Next: Give a parser the exact bytes it may read](14-readable-spans-and-terminators.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](12-design-a-build-service.md)
