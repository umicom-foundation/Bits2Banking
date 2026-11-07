<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/25-interpret-source-and-service-count-changes.md

PURPOSE:
Interpret source and service-count changes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Interpret source and service-count changes

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

Two observations are comparable only when their context is understood. Imagine one build plans two services and another plans six. A completed count of three in the second build cannot be interpreted using the first build's expected total.

The comparator reports planned and completed separately. It also exposes a source identity change. Its job is to show the facts; deciding whether they indicate a regression requires the relevant configuration and logs.

1. Make a table containing capture label, source identity, mode, state, planned, completed and reason.
2. Copy each value from the accepted reports.
3. If source identities differ, inspect the matching boot plans before comparing progress.
4. If the later report entered recovery, follow its reason into the corresponding serial log.

A reason such as service-timeout narrows the investigation to a deadline. It does not tell you whether the service was slow, the deadline was unreasonable, a dependency was missing or a clock behaved incorrectly. Avoid changing the timeout merely to make the report look successful.

Requested recovery is also different from an unexpected startup failure. A user may deliberately choose recovery to inspect a machine. The mode field preserves that intent. The validator refuses impossible combinations, but it cannot prove the report's description is true.

**Exercise.** Describe the next evidence you would collect for two cases: matching source identities with a changed reason, and different identities with changed service totals. Include build revision, capture time and service configuration. Do not infer a successful physical-machine boot from a host-side parser test. Each layer answers a different engineering question.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/platform/boot_report.c).

## Continue learning

[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [Previous: Run the OS report-comparison command](24-run-the-os-report-comparison-command.md) · [Next: Design repeatable boot-evidence checks](26-design-repeatable-boot-evidence-checks.md)
