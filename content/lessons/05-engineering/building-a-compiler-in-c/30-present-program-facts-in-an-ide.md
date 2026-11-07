<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/30-present-program-facts-in-an-ide.md

PURPOSE:
Present program facts in an IDE

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Present program facts in an IDE

This module follows one small program from text to an inspectable instruction sequence. Each lesson defines its terms, shows a concrete operation and gives an exercise with an expected observation. Inspection describes the program; execution attempts its arithmetic. A compiler, an IDE and a teaching tool can all use the same library contracts.

A terminal is a window in which commands are typed. A compiler translates source text into instructions; CMake describes a build and Ninja carries out its steps. Install Git and the MSYS2 UCRT64 GCC, CMake and Ninja packages if these tools are not available. The [Learning Build Systems course](../../../courses/learning-build-systems/index.html) explains their roles in more depth.

1. Keep the Umicom C and Bits2Banking checkouts beside each other in a folder you choose. The examples use C:\umicom. Replace that location consistently if yours differs.
2. In the MSYS2 UCRT64 terminal, install the tools with the following command. Complete the package manager's normal update instructions first if it requests them.

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

3. Open PowerShell and build the small compiler. Run each line separately. If a command reports an error, stop and read it before continuing.

```powershell
Set-Location "C:\umicom\umicom-c"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-debug -DBUILD_TESTING=ON
cmake --build --preset windows-ucrt64-debug --parallel 2
ctest --preset windows-ucrt64-debug --output-on-failure --no-tests=error
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" inspect ".\examples\inspection.uc"
```

On Linux, install a C23-capable C compiler, CMake and Ninja with your distribution's package manager. From the umicom-c checkout use the native-debug preset:

```bash
cmake --preset native-debug -DBUILD_TESTING=ON
cmake --build --preset native-debug --parallel 2
ctest --preset native-debug --output-on-failure --no-tests=error
./build/native-debug/bin/umicom-c inspect ./examples/inspection.uc
```

The inspection example should report 7 instructions, a peak stack of 3 values, 3 constants, 3 arithmetic operations and 71 encoded bytes. These are expected results to check on your machine. The language currently supports one integer-returning main function with arithmetic; it does not compile the full C language. If inspect is an unknown command, check that the binary was rebuilt from source containing umc_inspect. Keep any previous logs when investigating a failure.


## Keep the engine separate from the interface

An IDE helps people edit, build and run programs. The inspection engine answers a smaller question: what valid instruction sequence and resource counts does this source produce? A user interface should call the engine or its CLI rather than reimplementing the parser and stack rules.

Umicom Framework already owns project recipes that generate the small-language build workflow. Studio consumes those shared services. The inspection API supplies a reusable compiler capability; a polished inspection panel remains a separate integration task with its own UI qualification.

## Plan a truthful interaction

1. Identify the source document and its revision before starting work.
2. Compile its text into a caller-owned bounded instruction buffer.
3. Inspect only after compilation succeeds.
4. Display instruction count, peak values and encoded bytes with their units.
5. Label the report as structural inspection, with execution status shown separately.
6. If the user edits the document while a worker runs, discard or clearly mark the older result instead of attaching it to the new text.

A revision is an identifier for a particular state. It need not be a Git commit: an editor can use a monotonically increasing document-change number. The important property is that the result is associated with the exact text it described.

## Avoid misleading controls

An Inspect button should not execute the program or save it to an unexpected location. A Run button should display its selected budget and report arithmetic failure honestly. Disable commands only when there is a clear unmet requirement, and explain that requirement near the relevant control.

## Exercise

Sketch a small report with five fields and two statuses: compilation and execution. Add an example for valid arithmetic and another for division by zero. Write the expected text in each field before coding a widget.

Then read the Framework recipe source linked below. Locate where source checks, preview execution and test commands are generated. Keep compiler inspection in Umicom C, workflow coordination in Framework and presentation in Studio. This division lets command-line users, lessons and desktop tools share behavior without pretending that an authored API proves a complete GUI workflow.

## Read the source

[Open the example source](../../../../../Umicom-Applications/framework/src/developer_project/templates/umicom_c_preview.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Design boundary tests for a virtual machine](29-design-boundary-tests-for-a-virtual-machine.md)
