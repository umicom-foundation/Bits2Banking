# Watch and learn

The video series follows the same subjects as the written lessons. Each script includes a spoken explanation, examples and suggested on-screen demonstrations. Read the corresponding lesson alongside the video and try the practical exercise after watching.

## Video scripts

- [What is a computer?](scripts/01-what-is-a-computer.md) — about 7 minutes. [Written lesson](../lessons/01-computers/01-inside-a-computer.md).
- [How Git keeps track of your work](scripts/02-git-and-your-first-change.md) — about 8 minutes. [Written lesson](../lessons/05-engineering/16-git.md).
- [Understanding Umicom Framework](scripts/03-understanding-umicom-framework.md) — about 9 minutes. [Written lesson](../lessons/06-umicom/23-introducing-umicom.md).

- [Service through knowledge and technology](scripts/04-service-through-technology.md) — approximately 8–10 minutes. [Faith and technology reading](../v001_islam_blueprint_for_life/faith-service-and-technology.md).

The video pages can also be read as transcripts. Published video links can be added alongside the scripts as each recording becomes available.

## Build and boot episodes

- [Build a web server in C](scripts/05-build-a-web-server-in-c.md) — an illustrated 18–22 minute demonstration from HTTP to local browser preview.
- [From Assembly to Umicom Kernel](scripts/06-from-assembly-to-umicom-kernel.md) — a 20–25 minute walk through the RISC-V entry path and QEMU console.

- [HTTP byte scanning in C and Assembly](scripts/07-http-scanner-assembly.md) — a 9–12 minute source walkthrough with tests.
- [From Markdown to a working website](scripts/08-building-and-previewing-the-website.md) — a 12–16 minute build and preview demonstration.
- [Building a book manuscript in C23](scripts/09-assembling-a-markdown-book-in-c.md) — a 15–20 minute introduction to manifest-led publishing.
- [Find and fix a failing build boundary](scripts/10-find-and-fix-a-build-boundary.md) — a 12–15 minute demonstration of environment selection, child-process tests and local website preview.
- [Build, verify and publish one learning site](scripts/11-publish-and-verify-the-learning-site.md) — a 12–16 minute lesson connecting BookForge, MkDocs, native integrity checks and GitHub Actions.

## Processor and memory-safety episodes

- [How C calls Assembly functions](scripts/12-calling-c-from-assembly.md) — 16–20 minutes; [written lesson](../lessons/03-native-code/53-call-assembly-from-c.md).
- [Turn values into safe bytes with C23](scripts/13-binary-records-and-safer-c.md) — 14–18 minutes; [written lesson](../lessons/03-native-code/55-write-a-safe-binary-record-in-c.md).

- [Who owns this memory? Build a Notes model in C23](scripts/14-why-memory-ownership-matters.md) — 15–18 minutes; [Lesson 58](../lessons/03-native-code/58-memory-ownership-in-c23.md).
- [Checked arithmetic and safe website previews](scripts/15-checked-arithmetic-and-safe-preview.md) — 17–22 minutes; [Lesson 59](../lessons/03-native-code/59-checked-arithmetic-and-money.md) and [Lesson 62](../lessons/05-engineering/62-build-and-preview-the-education-site.md).
## Website repair and reliable native programs

- [Fix a broken website configuration](scripts/16-fix-the-website-configuration.md) — 11–14 minutes.
- [Test failures before they reach users](scripts/17-test-memory-and-network-input.md) — 18–22 minutes.

## New low-level programming episodes

- [Episode 18 — Who owns the memory? Pointers and arenas](scripts/18-where-does-the-memory-go.md)
- [Episode 19 — Review a learning website with C23](scripts/19-review-a-c23-navigation-audit.md)

## Compiler and kernel episodes

- [Episode 20 — From C23 source to a linked application](scripts/20-from-c-source-to-linked-application.md) — 15–19 minutes with the course catalogue library.
- [Episode 21 — Inside ELF, PE and Umicom Kernel](scripts/21-inside-elf-pe-and-umicom-kernel.md) — 17–22 minutes from binary headers to RISC-V first boot.

## Native build and cross-compilation episodes

- [Episode 22 — Build a C23 library and read the linker map](scripts/22-build-a-static-library-and-read-the-linker-map.md) — approximately 12–16 minutes; [Lessons 77–78](../lessons/05-engineering/77-understand-static-archives.md).
- [Episode 23 — Cross-compile C23 and RISC-V64 Assembly](scripts/23-cross-compile-c23-and-riscv64-assembly.md) — approximately 11–15 minutes; [Lesson 80](../lessons/05-engineering/80-cross-compile-c23-riscv64.md).

## Linker and ELF inspection episodes

- [Episode 24 — Where does the linker find a function?](scripts/24-where-does-the-linker-find-a-function.md) — approximately 16–20 minutes, showing C23/Assembly compilation, symbols, relocations and linker failures.
- [Episode 25 — Inspect ELF symbols and understand a kernel memory layout](scripts/25-elf-symbols-and-umicom-kernel-memory.md) — approximately 17–22 minutes, connecting defensive ELF parsing to Umicom Kernel bootstrap and sections.


## Memory management and kernel development

- [Episode 26 — From an ELF File to a Memory Layout](scripts/26-from-elf-file-to-running-address-space.md) (11–14 minutes): programme headers, zero fill and physical frame ownership.
- [Episode 27 — Virtual Memory, Sv39 and Umicom Kernel](scripts/27-sv39-virtual-memory-and-umicom-kernel.md) (14–18 minutes): page tables, permissions, kernel source and hardware qualification.


## Processes and memory protection

- [Episode 28 — A Program, Its Address Space and a Page Fault](scripts/28-process-address-spaces-and-page-faults.md) — 15–19 minutes with a C23 mapping exercise.
- [Episode 29 — Protect Executable Memory and Model a Process Lifecycle](scripts/29-wx-memory-policy-and-process-lifecycle.md) — 17–21 minutes, Framework W^X inspection and kernel-process state transitions.

## Kernel services and IPC episodes

- [Episode 30 — From a Notes event to a copied IPC message](scripts/30-from-a-notes-event-to-a-copied-ipc-message.md) (9–12 minutes): copy ownership, recipient refusal and a bounded C23 channel.
- [Episode 31 — System calls, IPC traces and Kernel ownership](scripts/31-system-calls-ipc-traces-and-kernel-ownership.md) (10–13 minutes): request validation, read-only traces, and actual Umicom Kernel source.

## Scheduling, blocking IPC and kernel ownership episodes

- [Episode 32 — How the scheduler gives each task a turn](scripts/32-how-the-scheduler-gives-each-task-a-turn.md) (11–14 minutes): work through the Ready/Running/Waiting queue and generation-tagged handles.
- [Episode 33 — Waiting for messages and closing services](scripts/33-blocking-ipc-cancellation-and-kernel-ownership.md) (12–16 minutes): build a Notes service, test a blocked receive, and read Umicom Kernel ownership contracts.


## Timers, events and recovery episodes

- [Episode 34 — Why deadlines use monotonic clocks](scripts/34-why-deadlines-use-monotonic-clocks.md) (11–14 minutes): checked arithmetic, a reproducible C23 timer and the difference between wall time and elapsed progress.
- [Episode 35 — Event signals, timeouts and Umicom Kernel](scripts/35-event-wakeup-and-umicom-kernel.md) (15–19 minutes): service composition, cancellation, a native trace inspector and the actual RISC-V Kernel trap/scheduler source.

## Interrupt ownership and recovery videos

- [Episode 36 — Who owns a hardware interrupt?](scripts/36-who-owns-a-hardware-interrupt.md) (13–17 minutes): source leases, masking, critical sections and actual Umicom Kernel contracts.
- [Episode 37 — Recover a service and inspect interrupt traces](scripts/37-recover-a-service-and-inspect-interrupt-traces.md) (14–18 minutes): accepted Notes revisions, explicitly reviewed retry, safe byte parsing and Kernel source boundaries.


## Interrupt diagnostics and driver lifetimes

- [Episode 38 — Trace a device fault with C23](scripts/38-trace-a-device-fault-with-c23.md) — approximately 12–15 minutes, ordered observations and a SHA-256-linked classroom trace.
- [Episode 39 — Driver lifetimes and retained evidence](scripts/39-driver-lifetimes-and-retained-evidence.md) — approximately 14–18 minutes, a reusable C23 driver model, bounded diagnostics and authoritative Kernel references.


## Device I/O and completion ownership

- [Episode 40 — Follow a device request through C23](scripts/40-follow-a-device-request-through-c23.md) (approximately 10–13 minutes): from a Notes Save request to a collected completion.
- [Episode 41 — Cancellation, completion queues and Kernel drivers](scripts/41-cancellation-completions-and-kernel-drivers.md) (approximately 11–15 minutes): cancellation races, read-only traces, VirtIO reset ownership and durability boundaries.
