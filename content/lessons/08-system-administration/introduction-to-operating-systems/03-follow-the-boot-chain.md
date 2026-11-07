<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/03-follow-the-boot-chain.md

PURPOSE:
Follow the path from firmware to a working console

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Follow the path from firmware to a working console

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

## What happens before main?

A desktop C program starts after its operating system has already prepared a process. A kernel must participate in preparing that environment. Firmware is early software supplied by a board or emulator. A bootloader selects and loads the next program. The kernel establishes the machine state required by its services and programs.

Assembly is a textual form of processor instructions. Early entry code uses it for operations that need exact register and machine-state control. C then expresses larger algorithms. Neither language removes the need to understand which memory and devices are available.

## Inspect the native route

1. Open arch/riscv64/boot.S in Umicom Kernel.
2. Find its entry label and the branch or call into C. A label names a location; it is not a C function declaration.
3. Identify the stack setup. The stack holds call data and local storage used while functions run.
4. Follow the referenced C entry point in the repository. Record initialization stages in their actual order.
5. Compare the interactive system target with the diagnostic target described in FIRST_SYSTEM_SESSION.md.

Do not modify boot registers by trial and error on a physical machine. Begin with the documented emulator profile and preserve a known-working image.

## A useful failure boundary

If no first console marker appears, investigate entry, memory layout and the serial device before blaming the shell command parser. If the banner appears but a command is rejected, the processor has already executed substantial startup code. That observation narrows the search without proving every earlier subsystem is correct.

Create a table with stage, source file, expected marker and possible failure. Leave an unknown marker blank until you locate its real writer. Invented success messages make troubleshooting harder.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Distinguish the development host, guest and build target](02-host-guest-and-target.md) · [Next: Understand memory, addresses and ownership](04-memory-and-ownership.md)
