# Native work-dispatch laboratory — Update 30

**Bits2Banking · Umicom Foundation · Sammy Hegab · MIT**

This independent teaching laboratory composes the **existing** Update 29 work-handoff C23 library and the **existing** completion-queue C23 library from an earlier course. It does not copy or modify their code in the update package, and it is not yet a production Umicom Framework module.

## Build prerequisite

The following paths must already exist in the full Bits2Banking checkout:

```text
labs/native/work-handoff/handoff.h
labs/native/work-handoff/handoff.c
labs/native/completion-queue/queue.h
labs/native/completion-queue/queue.c
```

Merge the earlier batches first if those paths are absent. This project deliberately refuses to compile when its dependencies cannot be found; it does not generate replacement or duplicate implementations.

## C23 interface contract

- `BtbDispatchSubmit` deep-copies 1–96 request bytes into the existing eight-slot work queue.
- `BtbDispatchStep` synchronously processes **one** queued item. It refuses work when the existing four-slot completion queue is full.
- `BtbDispatchRun` accepts a finite budget of 1–8 synchronous operations, never starts a thread and may finish fewer items than its budget.
- `BtbDispatchCancel` only cancels **queued** work and produces an explicit terminal notification. Cancellation is refused without state mutation if the completion FIFO is full.
- `BtbDispatchReceive` copies a terminal receipt into caller-owned storage and releases the original work slot after consuming the notice.
- `BtbDispatchQuiesce` stops admitting new requests; `BtbDispatchDrained` requires that **all** notifications have been consumed and all original slots have been released.
- `BtbDispatchInvariants` checks the composition's counters, records, token generations and notification mappings. The dispatcher must have a single owner; there are no thread-safety guarantees.

The request IDs are monotonic during an instance's lifetime and cannot silently wrap. Diagnostic digests are deterministic FNV-1a values **for educational comparison only**. They are not cryptographic hashes, safety controls or evidence of payment/trade correctness. The demo is not connected to any socket, broker or bank.

## Windows UCRT64 build — interactive PowerShell commands

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\work-dispatch" -B ".\output\learning-build\work-dispatch" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-dispatch" --parallel 2
ctest --test-dir ".\output\learning-build\work-dispatch" --output-on-failure
& ".\output\learning-build\work-dispatch\btb-work-dispatch-demo.exe"
```

**Expected**: nine CTest cases registered and passing, and a terminal demo line containing `PASS (3/3 delivered)`.

## Tests

| Name | What it checks |
|---|---|
| `fifo` | Original queued order, receipt correlation, counters. |
| `capacity` | Work queue full, downstream backpressure, cancellation refused before available notice space. |
| `cancel` | One cancellation notice and no loss of surviving work. |
| `stale` | Reused slots reject old identities. |
| `quiesce` | Quiescence and undelivered terminal records. |
| `invalid` | Reject invalid size/pointers/budget and request ID overflow. |
| `ownership` | Input copied before mutation and receipt valid after slot release. |
| `stress` | 80,000 deterministic state mutations plus controlled drain. |
| `demo` | Mock report request lifecycle. |

## Boundary and further work

Before any production integration, inspect the Umicom Framework scheduler, event bus, service lifecycle, command contracts and existing OS and UI threading models. Add real workers only after designing synchronisation, wakeups, cancellation acknowledgements, failure containment, resource exhaustion handling and testable shutdown. No Framework source or application source was modified by this batch.
