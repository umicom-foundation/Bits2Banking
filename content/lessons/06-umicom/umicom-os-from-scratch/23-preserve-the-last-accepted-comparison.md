<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/23-preserve-the-last-accepted-comparison.md

PURPOSE:
Preserve the last accepted comparison

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Preserve the last accepted comparison

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

An output parameter is a pointer through which a function returns a result. If a function writes half a result and then fails, its caller may accidentally display an inconsistent state. The report comparator follows a simple rule: either publish one complete mask or leave the previous value unchanged.

The function first validates both input reports. Only then does it compute a local mask. The final assignment is its publication point. There is no file access, allocation or asynchronous callback in this comparison.

1. Locate the saved variable in the lab. It keeps the mask from a successful comparison.
2. Follow the malformed-report call and its expected INVALID_ARGUMENT status.
3. Read the check that changes still equals saved.
4. Explain what a graphical report viewer should display when a newly selected report is refused.

A suitable viewer keeps the earlier accepted comparison and shows a separate error for the rejected selection. It must not label that earlier comparison as belonging to the rejected file. Keeping output bytes unchanged is necessary, but the surrounding UI still owns clear state and provenance labels.

The output must be separate writable storage, as the API contract states. A pointer into an input report would violate that contract. Inputs can be the same report when checking equality, but no other thread may mutate either report during the call.

**Exercise.** Write a three-column table with input, status and visible result. Include valid comparison, malformed first report and malformed second report. The latter two should retain the old accepted value while clearly displaying that the new comparison did not succeed. This pattern also applies to document imports, configuration previews and account statement reviews.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/platform/boot_report.c).

## Continue learning

[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [Previous: Compare fields with a change mask](22-compare-fields-with-a-change-mask.md) · [Next: Run the OS report-comparison command](24-run-the-os-report-comparison-command.md)
