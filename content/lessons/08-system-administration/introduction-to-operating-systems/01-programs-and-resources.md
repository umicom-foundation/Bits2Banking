<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/01-programs-and-resources.md

PURPOSE:
Understand programs and the resources they use

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand programs and the resources they use

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

## Start with one program

A program is a set of instructions. Source code is the human-readable form; an executable contains instructions the target computer can run. A running instance is called a process. Opening two copies of an editor usually creates separate running instances even though they came from the same executable file.

The boot-report client needs processor time to execute, memory for its variables, access to a chosen input file, and an output stream for text. These are resources. The operating system mediates access so programs do not each have to implement storage drivers or decide which process runs next.

~~~text
program request -> operating-system service -> device or managed resource
                 <- result or error          <- observation
~~~

## Follow a real request

1. Open main.c and find main. This is the entry function for this hosted C program.
2. Read argc and argv as the count and list of command-line arguments. The first argument names the program itself.
3. Find UmiBootReportLoad. Framework combines input-file checks with a parser; the platform adapter eventually asks the host to open and read a file.
4. Find printf. It writes a presentation of accepted fields, not a request to start a new OS.
5. Find return 1 and return 2. Nonzero process results let a caller distinguish failure from a successful observation.

## Try a prediction

If the file does not exist, should the program print ready from an uninitialized structure? No. The status is checked before the structure is read. A failed request is an ordinary result that must be handled. An OS service can fail because a resource is absent, permission is denied or input changed; software must not assume that every request succeeds.

Write a resource list for a text editor: a document file, memory for text, keyboard events and a display surface. Then add an audio application: it also needs an audio device and timing. Shared mechanisms belong in Framework; application-specific choices remain in the client.

## Read the source

[Open the example source](../../../../labs/framework/boot-report/main.c).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Next: Distinguish the development host, guest and build target](02-host-guest-and-target.md)
