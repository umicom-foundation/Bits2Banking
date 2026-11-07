<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cmake/01-follow-source-to-program.md

PURPOSE:
Follow source files to a running program

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Follow source files to a running program

CMake describes how a software project is prepared for building. In this course you will follow a small C project from source files to executables, understand dependencies, run tests and record useful evidence. Every chapter includes the setup needed to enter the exercise directly.

## Start here

A terminal is a window in which you type commands. A folder groups files; a path tells a command where a file or folder is. Source files contain the instructions people edit. A build folder contains the machine-readable results. Keep the two folders separate.

This course uses the existing labs/native/bounded-ledger-line project in Bits2Banking. It decodes a fictional message such as 1001:+2500: training account 1001, with a change of 2500 pence. It does not connect to a bank.

On Windows, install MSYS2. In its UCRT64 terminal install the tools:

~~~bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
~~~

Open PowerShell. Adjust the repository path if your copy is elsewhere. Run each line separately and stop on an error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
gcc --version
ninja --version
cmake -S labs/native/bounded-ledger-line -B build/ledger-line -G Ninja -DBUILD_TESTING=ON
cmake --build build/ledger-line --parallel 2
ctest --test-dir build/ledger-line --output-on-failure --no-tests=error
~~~

Use CMake 3.24 or newer and a compiler with C23 support. On Linux, install these tools through the distribution's package manager, open Bash in the repository, and use the same three cmake/ctest commands. The small project builds independently of Framework. [Learning C](../../../courses/learning-c/index.html) gives a slower installation walkthrough.

The expected test names end in syntax, mutations and example. Missing tools, missing executables and zero selected tests need investigation. For experiments, copy the lab to a separate practice folder and point -S at that folder; preserve the original example.


## What you will learn

Identify configure, compile, link and run as separate activities. No programming knowledge is needed for this first inspection.

Open main.c with a text editor. An editor changes characters; it does not execute them. Find main, the entry function called when the executable starts. Find BtbLedgerLineParse. It is declared in ledger_line.h and implemented in ledger_line.c.

A declaration describes a function's name, inputs and result type. Its implementation supplies instructions. A compiler translates one source file into an object file. The linker joins objects and libraries and resolves calls between them. An executable is the resulting program.

~~~text
main.c --------> main object ----------+
                                      +--> demo executable --> output
ledger_line.c -> ledger object -> library
ledger_line.h -> declarations used by both source files
~~~

CMake reads CMakeLists.txt and generates rules. Ninja follows those rules. The C compiler performs compilation.

## Try it

1. Complete Start here and read each command's result.
2. In PowerShell run & ".\build\ledger-line\bits2banking-ledger-line-demo.exe".
3. In Bash run ./build/ledger-line/bits2banking-ledger-line-demo.
4. Expect Training account 1001: change +2500 pence.
5. In your practice copy change the final two digits of the message to 25. Build and run again. Predict the result first.

Saving source does not update an already-built executable. Running before a successful rebuild can show old behaviour.

## Troubleshooting

“Command not found” means the shell could not locate a tool or program. A compiler diagnostic naming main.c means compilation began and found a source problem. An undefined reference names a missing implementation during linking.

## Check your understanding

Why can compilation accept a call while linking fails? The declaration describes the call; the linker still needs its compiled implementation. Summarise this distinction before continuing.

## Read the source

[Open the example source](../../../../labs/native/bounded-ledger-line/main.c).

## Continue learning

[Course contents](../../../courses/learning-cmake/index.html) · [Next: Read a CMake project one command at a time](02-read-a-cmake-project.md)
