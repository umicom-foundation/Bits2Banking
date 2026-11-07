<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/08-system-calls-and-framework.md

PURPOSE:
Locate the boundary between kernel services and Framework

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Locate the boundary between kernel services and Framework

An operating system coordinates programs, memory, devices and access to resources. This course introduces each idea using a small Umicom example. It assumes no previous operating-system or C experience. Definitions and setup are repeated where a lesson can be read independently.

## Prepare this lesson

You need a text editor to read the examples. A terminal is a window in which a typed command asks a program to do something. PowerShell is the Windows terminal language used below; Bash is the Linux alternative. A path names a file or folder. Replace C:\umicom with your checkout location if it differs.

For the optional C lab, install a C23 compiler, CMake and Ninja, and a matching Umicom Framework SDK that includes the platform component. On Windows, open PowerShell and enter:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\boot-report"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
gcc --version
~~~

Read the lab README before configuring it. Run commands separately and stop on a nonzero exit status. Reading a report does not boot an operating system. QEMU exercises use the separate Kernel guide linked in the relevant lesson; no physical disk is attached. You can complete the prediction and source-reading exercises without executing programs.

## Layers with different responsibilities

A system call is a controlled request from a program to an operating-system service. A library function is code called within the program's normal environment. A library may use system calls, combine several operations or perform a calculation entirely in memory.

Umicom Framework provides reusable services for applications. It does not need to become part of every kernel. The native Kernel and the minimal OS recovery controller have their own narrow dependencies; normal user-space programs can use Framework after the OS has supplied the environment they need.

~~~text
thin application: chooses a report and displays fields
Framework: validates file admission and report structure
host OS: provides the underlying file operations
hardware or emulator: carries out device activity
~~~

## Trace two functions

UmiBootReportParse accepts borrowed bytes and performs no file access. UmiBootReportLoad accepts a path and uses the shared input-file service before calling the parser. Keeping these separate makes it possible to test parsing without a filesystem and to reuse the parser for bytes obtained through another approved input route.

1. Find both public declarations.
2. Record each input, output and status contract.
3. Find the single canonical parser call in the loader.
4. Check that the application does not copy the parser into its own source.
5. Decide where a future GUI file chooser belongs: presentation in the client, reusable loading and validation in Framework.

An API is the source-level interface. An ABI also includes compiled calling conventions and data layout. An installed header and library must agree. Linking against an older archive while reading a newer header can fail even if the application source appears correct.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/platform/boot_report_file.h).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Distinguish a file interface from durable storage](07-files-and-persistence.md) · [Next: Read a boot observation without overstating its meaning](09-read-boot-observations.md)
