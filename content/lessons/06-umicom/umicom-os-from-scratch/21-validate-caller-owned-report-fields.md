<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/21-validate-caller-owned-report-fields.md

PURPOSE:
Validate caller-owned report fields

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Validate caller-owned report fields

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

A public C structure can be filled by a parser or directly by application code. A type declaration alone does not guarantee that its values are meaningful. An integer cast can produce an unknown enumeration value, and a character array can lack a string terminator.

UmiBootReportValidate applies the same field rules to both origins. It accepts only known modes and states, service counts within the declared limit, a recognised reason and a complete lowercase hexadecimal source identity. It checks that the reason contains a zero byte within its 32-byte array before treating it as a string.

1. Find the final part of main.c where memset fills later.reason with x characters.
2. Count the bytes filled using sizeof later.reason. This operation stays inside the array.
3. Find memchr in the Framework validator. Its size argument limits the search to that array.
4. Follow the return before strcmp when no terminator is present.

The defect being demonstrated is not memset itself. The deliberately constructed value is unsuitable for a string-reading operation. Calling an unbounded string function on it could continue reading beyond the array. Bounded admission prevents that operation from occurring.

**Exercise.** Replace the deliberate x-filled reason with the terminated text unknown. The record is still invalid, but now because its vocabulary is unsupported. Explain the difference between a missing terminator and a recognised-length value with an unknown meaning.

Validation assumes the report pointer refers to a complete accessible object. It cannot repair a dangling pointer to freed memory. Keep the object alive and prevent another thread from changing it during validation. These ownership requirements complement field checks; neither replaces the other.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/platform/boot_report.c).

## Continue learning

[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [Previous: Follow the boot-report parser](20-follow-the-boot-report-parser.md) · [Next: Compare fields with a change mask](22-compare-fields-with-a-change-mask.md)
