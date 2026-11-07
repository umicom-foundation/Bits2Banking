<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/26-design-repeatable-boot-evidence-checks.md

PURPOSE:
Design repeatable boot-evidence checks

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Design repeatable boot-evidence checks

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

A regression check records behaviour that should remain true after future changes. It is most useful when it targets a real boundary: malformed input must be refused, accepted input must produce the right fields, and inspecting a file must not change that file.

The Framework comparison suite checks equal reports, independent changed fields, invalid enumerations, bounded strings, state relationships and unchanged output on failure. The OS command suite adds the process boundary: argument handling, Unicode filenames, exit codes and printed results.

1. Open Framework tests/os_foundation/test_boot_report_compare.c.
2. Find the semantic case. It changes unused bytes after the reason terminator while expecting equality.
3. Open OS applications/os/tests/check_boot_report_comparison.cmake.
4. Find the SHA256 measurements before and after command execution. They check that file bytes remain unchanged.

A digest is a compact value computed from bytes. A changed digest indicates changed bytes. It does not identify who changed them or authenticate their origin. Here it is a practical assertion that a read-only command did not modify its selected fixtures.

**Exercise.** Propose a test for an incomplete second report. State its expected exit code, which stream should contain the error, whether a success heading may appear, and whether the first input file may change. Then compare your proposal with invalid-after.

Run focused parser and command tests after changes to these components, then the broader qualification required for the release. Record the exact source revisions and toolchain alongside results. Authored test code is not evidence of a passing execution. Keep skipped or unexecuted checks visible so another contributor can see what still needs qualification.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/platform/boot_report.c).

## Continue learning

[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [Previous: Interpret source and service-count changes](25-interpret-source-and-service-count-changes.md)
