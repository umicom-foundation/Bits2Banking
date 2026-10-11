# Major Update 15 — Scheduling, Blocking IPC and Service Lifetimes

This release adds a read-only **native C23 scheduling-trace inspector** to the
Framework-owned `umicom-education` command, four new software-engineering
lessons, a source-reading Umicom Kernel lesson, two runnable C23 laboratories,
three SVG diagrams and two narrated educational video scripts.

## New Framework interfaces

The new public header is `framework/include/umicom/education/schedule_trace.h`.
It describes the explicit `UMISCH1` classroom format, its bounds and a
caller-owned report. `UmiEducationScheduleTraceInspect` accepts bounded bytes;
`UmiEducationScheduleTraceInspectFile` reads an ordinary local file. Both
report failures without publishing a partial summary. The independent native
CLI command is:

```text
umicom-education schedule-trace --file PATH
```

It checks fixed-length record boundaries, nondecreasing logical ticks, FIFO
dispatch, live task states, unique IDs and matching wait keys. It does not
claim to monitor the privileged Kernel scheduler, perform actual context
switches or inspect a live message queue. The existing `ipc-trace`, `binary`,
`archive`, `symbols`, `load-plan`, `memory-audit`, website and book commands
remain available.

## Two complete C23 laboratories

`labs/native/round-robin-scheduler` provides a small task scheduler with eight
slots, generation-tagged handles, a FIFO ready ring, explicit waiting and
error-preserving results. `labs/native/blocking-ipc-lifetimes` composes this
library **and the existing** `labs/native/bounded-channel` source rather than
introducing another queue. It demonstrates a wait that does not spin, a
message that remains queued after a consumer closes, a checked receive buffer
and cancellation of a pending task.

These laboratories are hosted, single-threaded teaching tools. They do not
replace Umicom Kernel's native scheduler, syscalls, checked user memory,
interrupt handling or task-identity rules.

## Website and book compatibility

Navigation extends the current learning index with Lessons 102–106 and Videos
32–33. The older 165 navigation targets are retained. The original *Islam:
Blueprint for Life* volume, including all ten historical chapters, continues
to be referenced. The batch does not replace publishing workflows, documents,
BookForge, the existing Windows renderer or the C web server.

## Qualification boundary

The new Framework and learning source builds and passes the CTest cases on
Linux with GCC and Clang, including an AddressSanitizer/UndefinedBehaviorSanitizer
configuration. Windows UCRT64 and the full MkDocs build require maintainer
execution against the real checkout. A completed native teaching test is not
evidence that the real Kernel, Umicom OS or GitHub Pages has been qualified.

## Next subject

The next course increment should introduce **timer events, finite waits,
monotonic deadlines and cancellation**, followed by a source-level study of
Umicom Kernel's machine timer, user scheduling and event-wait services.
