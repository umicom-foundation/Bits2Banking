# Major Update 16 — Timers, events and Kernel boundaries

Umicom Framework gains a **read-only native C23 timer/event trace inspector**.
Bits2Banking gains five practical chapters (107–111), two compiled C23
laboratories, three editable SVG diagrams and two complete educational video
scripts. No existing implementation, book, function or document has been removed.

## What the reader can now do

After working through the lessons, a learner can explain why timeouts use a
monotonic source, calculate and check a finite deadline without unsigned
wraparound, distinguish an event notification from the data it describes,
reason about an auto-reset or manual-reset event, and show why a task becoming
Ready does not make it immediately Running.

The new source examples continue the Notes/service/scheduler application used
in Updates 14–15. The timed-service project **links the exact existing
round-robin scheduler and new timer source**, instead of reimplementing either.
Its three automated tests prove early notification, exact-deadline timeout
precedence and safe cancellation, including overflow rejection.

## Native trace contract

The command is:

```text
umicom-education timer-trace --file TRACE_FILE
```

Its input is an explicitly bounded version 1 binary teaching trace:

- `UMITMR1\0` magic, 16-byte header, 32-byte records;
- 4,096 maximum records and 32 unique wait identities;
- little-endian integers and exact record ordinals;
- one current logical tick, changed only by strictly increasing ADVANCE;
- a WAIT has an event key and a checked optional finite interval;
- SIGNAL and CANCEL require the exact pending key/identity;
- ADVANCE settles every newly due finite wait before later signals;
- complete report publication only after **all** input is valid.

The parser reads ordinary explicitly selected local files. This is a small
educational format, **not** Umicom Kernel's trace format, a live interrupt
capture, an IPC service, authentication or a production audit log.

## Why the difference matters

Real Umicom Kernel uses hardware-backed timer/interrupt and user-continuation
mechanisms. In particular, `arch/riscv64/trap.S` owns privileged register
entry/exit; `kernel/user_scheduler.c` owns task continuation eligibility;
`kernel/events.c` owns remembered events and their completion ordering;
`kernel/user_ipc.c` owns a separate blocked-message path. The educational
C23 exercise never replaces those subsystems. See the [source-reading
lesson](content/lessons/06-umicom/111-follow-umicom-kernel-timers-and-events.md).

## Preservation and qualification

New implementation files use C23 only. CMake is required to compile and test
it; Markdown/YAML/SVG remain publication sources; existing MkDocs still needs
its Python renderer. This update adds no new Python programme or runtime
component. The original *Islam: Blueprint for Life* navigation remains intact.

Validated on the isolated reconstructed Update 15 baseline: **24/24 native
Framework CTests passed** under GCC and Clang ASan/UBSan; the deadline
laboratory passed 1/1, the timed-service laboratory passed 3/3, also under
both toolchains. The SVG files parse and render, MkDocs YAML parses, and 172
previously configured navigation entries remain alongside 7 new ones.

The full real MkDocs build, Windows UCRT64 qualification and hosted GitHub
Pages deployment must still be checked on the maintainer's checkout. Do not
interpret this paragraph as evidence that those environments passed.
