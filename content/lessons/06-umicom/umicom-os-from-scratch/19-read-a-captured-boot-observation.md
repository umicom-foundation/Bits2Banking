<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/19-read-a-captured-boot-observation.md

PURPOSE:
Read a captured boot observation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read a captured boot observation

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

A boot is the sequence that starts a computer's operating system. Firmware begins that sequence, a loader prepares the kernel, and the kernel starts the first user-space process. A report is a small record of what one part of that sequence observed. It is useful because a computer can stop before a graphical desktop appears.

The lab contains two text records named EARLIER and LATER. A C string is an array of characters ending with a zero byte. The report protocol itself ends with a newline. The call passes sizeof EARLIER - 1U so the C-only zero byte is excluded from the protocol.

1. Open labs/framework/boot-report-comparison/main.c in your editor.
2. Find the first record. Read its state, planned and completed lines.
3. Find the second record and identify the two different values.
4. Run the lab using the setup commands. Match each printed line to its source field.

Here, planned=2 means the report expects two service starts. completed=1 records one completion. It does not tell us which service, whether it remains alive, or why another service did not complete. Those questions require the matching service configuration and serial log.

The source line is a 64-character hexadecimal identity supplied by the producer. Keeping it lets us compare evidence with a particular build or plan. It is not a digital signature. Someone who can replace a report can also replace its source text.

**Check your understanding.** Explain why a saved ready report cannot prove the computer is healthy now. Write down the report capture time, build identity and source of the serial log as separate investigation notes. Do not add arbitrary fields to the protocol: its parser deliberately rejects unknown fields.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/platform/boot_report.c).

## Continue learning

[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [Next: Follow the boot-report parser](20-follow-the-boot-report-parser.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](18-design-a-service-recovery-checklist.md)
