# Update 17 — Interrupt ownership and safe service recovery

## Overview

The new course links hardware interrupt fundamentals to the real RISC-V architecture and the existing Umicom Kernel implementation. It uses ordinary C23 exercises to isolate state and ownership concepts before learners study privileged machine instructions.

## What changes in Umicom Framework

`umicom-education interrupt-trace --file` is a read-only C23 inspector. Its input is the explicitly versioned `UMIIRQ1` **classroom** format, not a real Kernel log or a standard interrupt protocol. It uses fixed 32-byte records with checked file length, sequence, source, owner, lease generation, logical tick and event codes. It refuses invalid transitions and leaves caller reports unchanged when parsing fails.

The command is implemented by two new source units (`interrupt_trace.h` and `interrupt_trace.c`), one native regression test, and additive edits to the existing standalone Umicom Education CMake and CLI files. All existing commands and tests remain available. The format is deliberately independent from Umicom Kernel's true interrupt-controller ABI.

## What changes in Bits2Banking

Five human-readable chapters (112–116) cover interrupt ownership, cancelling versus acknowledging accepted work, checked service failure and retry, binary trace inspection and direct study of Umicom Kernel interrupt and trap code. Two C23 laboratories demonstrate source ownership and a fictional Notes service revision checkpoint. The second reuses the first library. Two narration-ready educational video scripts and three SVG diagrams accompany the course.

The original *Islam: Blueprint for Life* manuscripts and all earlier lessons remain unchanged. The website navigation gains seven entries; no existing navigation entry is removed. The source language policy remains C23 first with Assembly reserved for real ISA and ABI requirements. CMake, Markdown, YAML and SVG serve their existing tooling and documentation purposes.

## Important boundaries

The classroom interrupt-source state machine never accesses RISC-V CSRs. It does not act as an interrupt service routine, manage actual hardware, execute user-mode transitions or claim processor privilege. `RECOVER` means an explicitly reviewed fictional state change; it is not guaranteed machine-state recovery. The fictional Notes checkpoint is kept only in RAM and does not supply durable transaction semantics. The teaching parser does not read production kernel events.

For true RISC-V interrupt behaviour, read Umicom Kernel's [`docs/INTERRUPT_OWNERSHIP.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/INTERRUPT_OWNERSHIP.md), [`kernel/interrupts.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/interrupts.c), [`arch/riscv64/trap.S`](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap.S) and [`kernel/trap_guard.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/trap_guard.c).

## Qualification

The complete reconstructed Update 16 baseline plus Update 17 source was configured and compiled under GCC and Clang with AddressSanitizer/UndefinedBehaviorSanitizer in the local Linux environment. The standalone Framework Education suite contained 26 passing CTest cases. Each new laboratory contained two passing cases under GCC and Clang sanitizers. New drawings were checked as SVG/XML, and the combined MkDocs YAML remained parseable. The new seven navigation paths exist and retain the original entries.

**Still to qualify:** the user's actual Windows UCRT64 checkout, the complete historical MkDocs site build with the original book manuscripts, GitHub Pages deployment, and any real QEMU/physical Umicom Kernel execution. The reconstructed documentation workspace does not contain every historic imported page; a complete MkDocs run must be performed against the maintainer checkout.
