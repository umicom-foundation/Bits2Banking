# Episode 61 — Cancellation, Late Completions and Shutdown

**Bits to Banking · Umicom Foundation** · Related chapters: 174 and 175

## Opening (00:00–01:15)

Show the browser requesting `/api/courses` and the native event loop returning to another connection. Ask the central question: who owns the request bytes while processing is pending? Explain that a pointer to a reused receive buffer is not an owned request.

## Segment A: the business example (01:15–04:30)

Use the Umicom Training Platform course list and a Studio diagnostics panel. Trace one request through request admission, queued work, acquisition and explicit completion. Keep the source in `handoff.c` visible beside the diagram. Explain queue capacity and the difference between waiting and active work.

## Segment B: read the implementation (04:30–10:00)

Open `handoff.h` and `handoff.c`, tracing `BtbWorkSubmit`, `BtbWorkAcquire`, `BtbWorkComplete`, `BtbWorkCancel`, `BtbWorkRelease` and `BtbWorkQuiesce`. Inspect `slot` and `generation`. Demonstrate why a stale token cannot be accepted after slot reuse. Do not describe this model as a multithreaded pool.

## Segment C: demonstrate test evidence (10:00–13:30)

Build with CMake and Ninja. Run CTest and the native C23 demo. Open `test_handoff.c`; point out FIFO, cancellation, generation, quiescence and 50,000 deterministic state mutation operations. Explain what these tests prove, and what they do not.

## Closing (13:30–15:00)

Ask learners to identify the resource owner at every transition. Explain how these same contracts apply to future reusable Umicom Framework services but require separate review before production or concurrent use.

## Recording checklist

- Show an actual Umicom-relevant workflow rather than an unrelated toy example.
- Keep compiler commands and expected test names on screen.
- Label the lab as **single-owner deterministic C23**.
- Do not imply the legacy server or the Framework was modified.
- Close with a short challenge: describe and test one stale-token failure.
