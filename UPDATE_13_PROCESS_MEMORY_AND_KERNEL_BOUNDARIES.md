# Major Update 13 — Processes, Page Faults and Executable Protection

## A memory boundary becomes a process boundary

The previous lessons explained ELF file layouts, static-library linking, frame ownership and RISC-V Sv39 translation. This update connects those parts to processes and their memory permissions.

The native Framework tool gains **`memory-audit --file ELF_PATH`**. It works entirely in hosted C23. A valid PT_LOAD byte range may occupy a partial memory page. Two separate byte ranges may share that page when rounded to 4 KiB boundaries, potentially demanding both write and execute access. The new command reports those page-level conflicts. It never loads the file, maps RAM, grants privileges or executes it.

The existing `UmiEducationElfLoadPlanInspectFile` owns the ELF parser. The memory-audit implementation consumes its validated result instead of implementing another ELF parser. Its sweep requires at most 128 boundary values for 64 loadable segments and does not allocate one record per declared virtual page. Invalid calls leave the caller's report unchanged. Unknown PT_LOAD permission bits are surfaced for review.

## Learning sequence

The new written lessons advance in five steps:

1. **Lesson 92** — an executable file becomes a process only after loader and OS work; distinguish virtual addresses, physical frames and ownership.
2. **Lesson 93** — permitted access, unmapped faults and protection faults; use a C23 page-access model with checked rights.
3. **Lesson 94** — why ELF permissions need page-level rather than only byte-range checks; run the native Framework memory audit.
4. **Lesson 95** — track NEW, READY, RUNNING, WAITING and TERMINATED process states with a failure-atomic C23 state machine.
5. **Lesson 96** — connect the concepts to RISC-V machine/supervisor/user modes, trap entry, `satp`, `sfence.vma` and original Umicom Kernel source.

Two native laboratories can be compiled on Windows and Linux using CMake/Ninja. They contain ordinary C23, not kernel-mode code. Both deliberately refuse operations rather than pretending to implement real hardware isolation. Three editable SVG figures and two narration scripts support website and video teaching.

## Source boundaries

The **Umicom Kernel repository** owns the privileged process registry, scheduler, memory management and trap handling. The **Umicom Framework repository** owns reusable hosted services and this read-only ELF audit. The **Bits2Banking repository** owns lessons and self-contained training models. The original *Islam: Blueprint for Life* book and all previous website navigation entries remain in place.

No user-space process has been created by this release, no kernel code changed and no complete ELF loader was implemented. A W+X finding is review evidence, not a final decision about a valid system-specific memory layout.

## Qualification

The update is built against a reconstructed Update 01–12 source baseline. On the Linux validation host, the Framework's **18 CTest cases passed under GCC and Clang with AddressSanitizer/UndefinedBehaviorSanitizer**. Each new training laboratory passed **2 CTest cases** on both toolchains. The real `umicom-education memory-audit` command reported zero W+X pages for the existing synthetic RISC-V ELF fixture. The three SVGs parsed and rendered. The full MkDocs renderer was unavailable in the isolated validation runtime; host Windows build, complete site rendering and deployment need separate acceptance.

## Next update

**Major Update 14 — System calls, IPC and message ownership.** Teach how an unprivileged application requests protected services, how messages cross component boundaries, and how channel ownership and back-pressure are tested. Refer directly to Umicom Kernel's message-channel and service source and reuse Framework communication contracts where relevant. Implement new runtime functionality in C23 with architecture-specific Assembly only where necessary.
