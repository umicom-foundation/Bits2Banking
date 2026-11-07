<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/12-from-emulator-to-release.md

PURPOSE:
Plan the route from a learning guest to an OS release

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Plan the route from a learning guest to an OS release

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

## An executable is not a bootable disk

An ELF file contains an executable in a defined format. A CD image or USB disk image also needs the structures expected by firmware and its bootloader. Renaming an ELF file to .iso does not create those structures. Copying it onto a USB drive does not select a compatible boot protocol.

A supported physical release must identify a machine or platform family, firmware mode, image format, storage layout and required drivers. It also needs a recovery procedure and a precise statement about whether it writes to disks. Those are engineering deliverables, not packaging labels.

## Build a qualification map

1. Record the exact source revisions and toolchain.
2. Record the target architecture and emulator or physical board configuration.
3. Keep configuration, build and test results separately.
4. Check boot entry, console, memory, services and shutdown with their own evidence.
5. Add persistence tests only when a storage route claims persistence.
6. Add account and desktop workflows only when those features exist.
7. Retain failed and skipped checks alongside successful ones.

The current Kernel first-session guide provides a diskless QEMU route. The OS Foundation guide provides a Linux-based QEMU bundle route. Neither guide promises a universal CD or USB installer. Continue with those documented environments while physical boot media is developed.

## Continue your project

Choose one narrow next question: how a memory region is allocated, how a timer resumes a task, or how a failed startup check reaches recovery. Read the corresponding source and write a prediction before changing it. Add a regression that would fail if your change were absent.

For deeper development, continue to Umicom Kernel from Scratch or Umicom OS from Scratch. Keep the host observation lab as a reusable example of presenting precise evidence without embedding privileged policy in the user interface.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BOOT_TARGETS_GUIDE.md).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Understand recovery, users and permission boundaries](11-recovery-and-account-boundaries.md)
