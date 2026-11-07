<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/24-run-the-os-report-comparison-command.md

PURPOSE:
Run the OS report-comparison command

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Run the OS report-comparison command

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

The small lab uses text already stored in the program. The OS command reads two files selected by the user. Its reusable file admission and parsing remain in Umicom Framework. The OS frontend handles command names and readable output.

An absolute path identifies a file without relying on the terminal's current folder. On Windows, a drive-qualified path such as C:\umicom\captures\earlier.report is absolute. Quote paths so spaces remain part of one argument.

1. Obtain two captured boot.report files from the boot runs you want to investigate. Keep the associated serial logs and build identities.
2. Save copies in a folder you choose, giving them different descriptive names.
3. From an already built OS checkout, run the following command with your actual paths:

~~~powershell
& "C:\umicom\umicomOS\build\windows-ucrt64-all-debug\bin\umicom-os.exe" --compare-boot-reports "C:\umicom\captures\earlier.report" "C:\umicom\captures\later.report"
~~~

4. Read each changed field. If no semantic fields changed, the command says so explicitly.

A return code of zero means the comparison was performed. Differences are valid results, so they do not produce a failure code. Code one means a read, validation, comparison or output problem. Code two means the command arguments were not recognised.

If a path is refused, verify that it names a regular local file with an absolute path. If the grammar is refused, check the file was captured as the report itself, not copied from a full console transcript. The wire format uses LF line endings. Preserve the original capture rather than silently rewriting it to make a parser accept it.

The command does not boot a guest, restart a service, install an OS or modify either input file.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/platform/boot_report.c).

## Continue learning

[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [Previous: Preserve the last accepted comparison](23-preserve-the-last-accepted-comparison.md) · [Next: Interpret source and service-count changes](25-interpret-source-and-service-count-changes.md)
