<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/04-memory-and-ownership.md

PURPOSE:
Understand memory, addresses and ownership

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand memory, addresses and ownership

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

## Storage while a program runs

Memory stores bytes that the processor can read and write. An address identifies a location in an address space. A C pointer holds a value used to access an object; the object must still exist and the access must remain within its valid bounds.

Physical memory describes the machine's storage locations. Virtual memory lets an OS map process-visible addresses to selected physical storage with access rules. A mapping is not an allocation policy by itself. A kernel must also track which regions are available, reserved or already owned.

## Connect the idea to the lab

The report client declares UmiBootReport report as local storage. UmiBootReportLoad receives its address and writes a complete result only on success. The parser copies strings into arrays inside the result; it does not leave pointers into a temporary input buffer. This ownership contract prevents a later caller from depending on input storage that has already gone away.

1. Read the structure in Framework's platform/boot_report.h.
2. Find reason[32] and sourceId[65]. These capacities include space for terminators.
3. Read the parser's temporary result variable and final assignment.
4. Explain why a rejected input cannot partially replace the caller's accepted report.
5. Open Kernel's physical_memory.c and identify the allocation and release entry points before following helper functions.

## Practice safely

Draw two boxes: input bytes and output structure. Draw the temporary result between them. Mark when each box is valid. Then cross out the input after parsing and check whether the output still refers to it. It should not.

A dangling pointer refers to storage whose lifetime has ended. Setting one pointer to NULL does not repair other copies. The practical rule is to identify one owner, document every borrow and end all borrows before releasing or replacing the owned object.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/physical_memory.c).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Follow the path from firmware to a working console](03-follow-the-boot-chain.md) · [Next: Understand processes and taking turns on a processor](05-processes-and-scheduling.md)
