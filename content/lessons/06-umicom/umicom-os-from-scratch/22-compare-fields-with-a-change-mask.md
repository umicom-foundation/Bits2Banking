<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/22-compare-fields-with-a-change-mask.md

PURPOSE:
Compare fields with a change mask

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Compare fields with a change mask

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

A change mask stores several yes-or-no answers in one unsigned integer. Each answer uses a different bit. Framework defines one bit each for mode, state, planned count, completed count, reason and source identity.

UmiBootReportCompare validates both reports before comparing their fields. The lab expects exactly the state and completed-count bits. The bitwise OR operator, written |, combines those two bits. To ask whether one bit is present, use bitwise AND, written &.

~~~c
if (changes & UMI_BOOT_REPORT_CHANGED_STATE) {
    puts("The captured state changed.");
}
~~~

1. Read the six UMI_BOOT_REPORT_CHANGED definitions in boot_report.h.
2. Draw six boxes labelled with the field names.
3. Mark only state and completed for the lab records.
4. Find the lab assertion that compares the whole mask with these two combined bits.

This assertion is more precise than checking changes != 0. A source change would be important too, and a broad nonzero check would miss an accidentally added or omitted bit.

Do not compare entire report structures with memcmp. C may place padding between fields, and unused characters after a terminator need not have the same value. Two records with the same semantic fields should compare equal even when those irrelevant bytes differ.

**Exercise.** Change only the first hexadecimal digit in LATER's source line. Predict the new bit before running. Then update your experimental assertion to include CHANGED_SOURCE. Keep the original lab unchanged for the standard exercise. A different source does not mean that one build is better; it means the evidence belongs to different identified inputs.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/platform/boot_report.c).

## Continue learning

[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [Previous: Validate caller-owned report fields](21-validate-caller-owned-report-fields.md) · [Next: Preserve the last accepted comparison](23-preserve-the-last-accepted-comparison.md)
