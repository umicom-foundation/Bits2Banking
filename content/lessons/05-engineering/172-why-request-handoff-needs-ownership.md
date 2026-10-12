# Chapter 172 — Why request handoff needs explicit ownership

**Bits to Banking · Engineering track · Umicom Foundation**  
**Implementation language:** ISO C23  
**Laboratory:** `labs/native/work-handoff`  
**Previous knowledge:** Chapters 167–171, HTTP request lifecycle and C structures.

## Why this matters

A browser sends a GET request for /api/courses. The socket reactor reads the bytes, but another component will process the request. Who owns the bytes while the first component returns to watching sockets? In a financial application, request identity and lifecycle are part of correctness. A response for an older portfolio snapshot must not be mistaken for a newer one. A cancelled account lookup must not unexpectedly change the current view. These are ownership and control questions, not just throughput questions.

## Learning objectives

Understand the difference between copying a request into a bounded queue and borrowing memory tied to a connection; explain why a disconnect must not invalidate queued work. By the end of this chapter, the reader should be able to describe the state changes, locate the corresponding C23 contract, build the executable laboratory and explain a rejected operation.

## Prerequisite check

Confirm that you can distinguish an array index from a stable request identifier, understand `size_t`, `uint64_t`, a pointer to caller-owned bytes, and why a fixed-size buffer must always be accompanied by an explicit length. Review the previous reactor lessons if the difference between a socket handle and a request object is unclear.

## Mental model: request work has a single owner

The reactor remains the owner of the accepted socket and its receive buffer. The handoff queue becomes the owner of *copied* request bytes. An acquiring consumer temporarily borrows a `const BtbWorkItem *` and must not free or mutate it. Completion changes the state, but does not itself recycle the storage. Only `BtbWorkRelease` clears the payload and makes the slot available for another generation. This deliberately explicit two-stage process makes ownership visible when debugging.

A token contains both `slot` and `generation`. `slot` makes lookup efficient. `generation` distinguishes a new request occupying an old slot. That distinction is particularly important in Studio diagnostics, Trader market-data panes and TMS workflow notifications, where late responses are normal.

## Formal contract

Open `labs/native/work-handoff/handoff.h` and locate `BtbWorkSubmit`. Read the parameters and result enumeration before reading the implementation. The queue has eight fixed slots and a 96-byte payload per slot. The fixed limits are chosen for inspectability, **not** as universal HTTP request limits. Unsupported or oversized input is rejected rather than truncated.

Copy the request bytes into the queue-owned payload, return a generation-bearing token, and never retain the reactor input pointer.

```c
BtbWorkQueue queue;
BtbWorkToken requestToken;
const char request[] = "GET /api/courses";

if (BtbWorkInit(&queue, 2U) != BTB_WORK_OK) {
    /* Report an initialisation error to the caller. */
}
if (BtbWorkSubmit(&queue, 1001U, request,
                  sizeof(request) - 1U, &requestToken) != BTB_WORK_OK) {
    /* Return a bounded-admission failure. */
}
```

`1001` is a teaching connection identifier, not an actual socket and not a security principal. A real Umicom service would use an authenticated request context and a correlation identifier governed by Framework contracts.

## Failure and recovery

If a request arrives with a byte length greater than BTB_WORK_BYTES, the queue rejects it with BTB_WORK_INVALID; this is a defined contract, not an accidental overflow. No test in this batch relies on a sleep, live socket, background thread or a remote server. A deterministic state machine makes it practical to review every transition with a debugger. **Important:** the laboratory is not yet a thread-safe producer/consumer queue. Do not call it from multiple threads without introducing an explicitly reviewed synchronisation and lifetime design.

## Build and inspect

From PowerShell, in the `Umicom-Bits2Banking` repository:

```powershell
cmake -S ".\labs\native\work-handoff" -B ".\output\learning-build\work-handoff" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-handoff" --parallel 2
ctest --test-dir ".\output\learning-build\work-handoff" --output-on-failure
```

These are interactive build commands, not a PowerShell script. All delivered executable project logic is written in C23.

## Guided laboratory

1. Read `handoff.h`, identifying the state enumeration and the token fields.
2. In `handoff.c`, follow `BtbWorkSubmit` to the precise state mutation.
3. Run the named CTest case or the `btb-work-handoff-test` executable.
4. Put a breakpoint before the state mutation and inspect `queue.queued`, `queue.active`, `item->generation` and `item->state`.
5. Repeat after a cancellation or release, and explain which operation owns the transition.
6. Record the observed state and the expected state in a short engineering note.

## Questions and exercises

1. **Recall:** Which component owns the copied request bytes after submission?
2. **Application:** What happens if the same token is completed twice?
3. **Debugging:** Which counters would you inspect after an unexpected `BTB_WORK_BUSY` result?
4. **Design:** How should a GTK4 view react when the request it launched becomes stale?
5. **Extension:** Design a nonblocking reactor adapter that can explicitly refuse excess work without retaining invalid pointers. Do not implement threads until the ownership and synchronisation contract is approved.

## Umicom connection

The lab is intentionally isolated in the educational repository. Shared production capabilities should be evaluated against existing Umicom Framework services before any migration. The Master Controller coordinates lifecycle and policy; a Slave Controller owns its domain request transitions. The Framework Data Server remains the sole persistence authority for Umicom-owned records. No application should duplicate a queue or bypass the approved Framework interfaces.

## What this chapter does not claim

The sample does not implement a concurrent worker pool, HTTP pipeline integration, distributed delivery, durable work persistence or new Framework features. These require separate design, implementation and testing. This distinction is essential when promoting educational examples into production services.

**Next:** continue the sequence through Chapter 176, then compare the sample with existing Framework scheduling and service abstractions before considering implementation reuse.
