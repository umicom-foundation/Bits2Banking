<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/02-host-guest-and-target.md

PURPOSE:
Distinguish the development host, guest and build target

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Distinguish the development host, guest and build target

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

## Three roles

The host is the computer running your development tools. A guest is a computer simulated or virtualized by a program such as QEMU. The build target is the environment for which a compiler emits instructions. These roles can differ: a Windows x86-64 host can build a RISC-V executable and run it in a RISC-V QEMU guest.

An instruction-set architecture defines the processor instructions and registers available to software. An operating-system interface adds services and executable conventions. Matching a processor alone is not enough: a RISC-V Linux program still expects Linux services that an experimental native kernel may not provide.

## Draw your setup

1. Write the name of the OS currently running your terminal.
2. Write the compiler path and target selected by the build preset.
3. Write the emulator command, if any.
4. Write the executable that will be loaded into the guest.
5. Keep generated Windows and cross-compiled build files in different directories.

The Kernel guide uses riscv64-clang-debug and umicom-system.elf. The Windows Applications preset builds host programs. Umicom OS Foundation builds a Linux kernel plus a root-filesystem archive. Each output serves a different execution environment.

## Interpret an error

Trying to launch an ELF file by double-clicking it in Windows does not test its kernel entry code. The host may not recognize the format. Similarly, a missing guest console can reflect a wrong board, UART or boot argument. Record the host, compiler, target and launch command before investigating application logic.

An emulator is useful because its devices and memory can be specified repeatably. Passing an emulator test remains evidence for that configuration; it does not qualify an arbitrary physical computer.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_SYSTEM_SESSION.md).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Understand programs and the resources they use](01-programs-and-resources.md) · [Next: Follow the path from firmware to a working console](03-follow-the-boot-chain.md)
