<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/20-follow-the-boot-report-parser.md

PURPOSE:
Follow the boot-report parser

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Follow the boot-report parser

Follow captured startup observations from bytes to a checked comparison. Use the real Framework parser, then inspect the OS command that consumes it.

You need a text editor, a terminal, CMake 3.24 or newer, Ninja and a C23-capable C compiler. A terminal accepts commands as text. CMake describes how a program is assembled; Ninja carries out the necessary compilation commands. A compiler translates C source into machine instructions. This lab runs on the current computer; it does not install or boot an operating system.

On Windows, install MSYS2 from its official installer, open its UCRT64 terminal and install the toolchain with the following command. Accept the package manager's prompts. If it requests a restart during a system update, complete that update first.

~~~sh
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
~~~

Obtain the Bits2Banking and Framework source checkouts. In these examples they are located at C:\umicom\Umicom-Bits2Banking and C:\umicom\Umicom-Applications\framework. Adjust the paths if you use another folder. Open PowerShell and enter each line separately, stopping if a command fails:

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S labs/framework/boot-report-comparison -B build/boot-report-learning -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/boot-report-learning --parallel 2
ctest --test-dir build/boot-report-learning --output-on-failure --no-tests=error
& .\build\boot-report-learning\bin\boot-report-learning.exe
~~~

On a Linux system with GCC, CMake and Ninja installed, place the checkouts beneath ~/umicom, open Bash, and use:

~~~sh
cd ~/umicom/Umicom-Bits2Banking
cmake -S labs/framework/boot-report-comparison -B build/boot-report-learning -G Ninja -DUMICOM_FRAMEWORK_SOURCE="$HOME/umicom/Umicom-Applications/framework"
cmake --build build/boot-report-learning --parallel 2
ctest --test-dir build/boot-report-learning --output-on-failure --no-tests=error
./build/boot-report-learning/bin/boot-report-learning
~~~

The expected output includes state: starting -> ready, completed: 1 -> 2 and Malformed report refused; previous comparison preserved. If CMake cannot find boot_report.c, check the source path. If comparison symbols are missing, the header and source must both contain the comparison API. Do not combine files from unrelated revisions. The build folder stores generated files; the labs folder contains the source you edit.

A parser turns a sequence of characters into values the program can use. Framework's UmiBootReportParse receives a pointer to the first character, a byte count and a pointer to an output structure. A structure groups related values under named fields.

The parser first checks the maximum length, exact version line and final newline. It then reads each line, finds its equals sign and recognises the field name. It records which fields have appeared. A repeated field is refused because accepting two different states would leave its meaning ambiguous.

1. Open Framework src/platform/boot_report.c.
2. Locate Number. Follow how each digit contributes to a value using result * 10U plus the next digit.
3. Locate the seen mask. Each field owns a different bit, so a duplicate can be detected before publication.
4. Locate UmiBootReportValidate near the final output assignment.

The local result begins at zero. The caller's output is replaced only after every field and relationship is valid. This is useful for a UI that must keep showing the previous accepted observation while a new file is rejected. A local variable with an uninitialised value must never be displayed after a failed call; main.c returns before using it.

**Exercise.** In a copy of the lab, change completed=2 to completed=3 while keeping planned=2. Rebuild and run. Expect a nonzero exit because more services cannot complete than were planned. Restore the record afterwards.

A parse error is evidence of an unacceptable record. It is not proof that a host was attacked. Record the actual bytes, source identity and producer version before deciding whether the cause was truncation, a wrong format, a software defect or malicious input.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/platform/boot_report.c).

## Continue learning

[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [Previous: Read a captured boot observation](19-read-a-captured-boot-observation.md) · [Next: Validate caller-owned report fields](21-validate-caller-owned-report-fields.md)
