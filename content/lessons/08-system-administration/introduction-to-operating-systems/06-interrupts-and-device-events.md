<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/06-interrupts-and-device-events.md

PURPOSE:
Understand interrupts and device events

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand interrupts and device events

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

## An event outside the current instruction stream

A device can need attention while a program is doing other work. An interrupt transfers control through a defined processor mechanism to a handler. A timer can generate such an event. An exception is commonly caused by the instruction being executed, such as an invalid access. The exact categories and saved registers are architecture-specific.

The interrupted program cannot simply lose its registers. Entry code saves the state required by the handler and later restoration. A trap frame is a structure representing that saved state. Its layout must agree with the assembly that stores and loads it.

## Read without guessing register roles

1. Open the Kernel's RISC-V user execution assembly.
2. Find the accompanying C declarations and trap-frame type through its include files.
3. Match a stored field offset to the corresponding structure field.
4. Find the return path and the state it restores.
5. Read a host test separately from an emulator test. Mark which one can exercise actual trap entry.

A C structure change can therefore break assembly even when each file compiles. Compile-time layout checks and an actual guest regression protect different parts of this boundary.

## A small reasoning exercise

Suppose the handler saves a pointer to temporary storage, then returns and later uses that pointer as the saved task frame. What can go wrong? The storage may no longer belong to that frame. Store owned values in a stable task record, and document when that record can be reused.

For device work, add a sequence diagram showing request, device completion, interrupt acknowledgement and resumed task. Do not invent acknowledgement rules from another device; read the selected device contract before changing a driver.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/user_execution.S).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Understand processes and taking turns on a processor](05-processes-and-scheduling.md) · [Next: Distinguish a file interface from durable storage](07-files-and-persistence.md)
