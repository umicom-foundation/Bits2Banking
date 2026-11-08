<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/37-qualify-a-freestanding-trace.md

PURPOSE:
Qualify a freestanding trace

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Qualify a freestanding trace

## Setup recap

This optional study follows the existing native Kernel program lesson. You need the Kernel RISC-V Clang toolchain and QEMU as well as the trace-enabled Umicom C source checkout. Follow Kernel docs/CVM_PROGRAM_GUIDE.md for the separate CVM build directory; a hosted Windows executable cannot run as the Kernel user program.

## Keep the interpreter inside its native envelope

The Kernel loads a native ELF program into user memory. That small program owns the bytecode, decoded instructions, result and trace storage. It interprets the arithmetic as data, checks the expected outcome, then uses the existing native EXIT call. The runtime has no Kernel pointers, host callbacks, heap calls or syscall interface.

Selectors 0 through 4 retain their earlier meanings. Selectors 5 through 8 add trace success, fuel exhaustion, arithmetic rejection and insufficient-storage checks. They report 0xc005 through 0xc008 when the expected condition is observed. The normal console prints these values in decimal: 49157 through 49160.

## Observe isolation as well as arithmetic

The diagnostic guest repeats the cases with runtime objects compiled at O0 and O2. These are two compiler optimization settings. Both links intentionally expose accidental hosted-library dependencies instead of discarding unused functions to hide them.

The existing monitor checks U-mode exit, refuses re-entry into an exited process and verifies that destroying the process restores its owned frames. A correct trace value does not replace these lifecycle checks. The source receipt now includes trace.h, so a changed or missing trace layout can invalidate earlier image evidence.

## Exercise and recovery

The added checks remain unqualified until executed on the relevant source and toolchain. A QEMU pass does not establish physical hardware support, a full C compiler or an OS debugger.

1. Read the expected selector table before launching anything.
2. After the owner has built and qualified the optional image, run selector 5 through the console and compare the decimal outcome.
3. Run selector 6, then selector 0 again, preserving the serial transcript.
4. If an older image rejects selector 5 with 49156, check the exact image path and build receipt before diagnosing an arithmetic bug.

## Read the source

[umicom-kernel/programs/cvm/main.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/programs/cvm/main.c). Read the matching checkout when qualifying your own build.

## Continue learning

[Course contents](index.md) · [Previous: Present a fresh Framework trace](36-present-a-fresh-framework-trace.md) · [Next: Record layered trace evidence](38-record-layered-trace-evidence.md)
