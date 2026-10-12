# Episode 38 — Trace a device fault with C23

**Approximate duration:** 12–15 minutes  
**Companion lessons:** [117. Understand interrupt diagnostics](../../lessons/05-engineering/117-interrupt-diagnostics-and-event-order.md), [120. Inspect a chained evidence trace](../../lessons/05-engineering/120-inspect-a-chained-evidence-trace.md)

## 00:00–01:30 — The problem: a failure message without a history

**Narration:**

A note-taking application has sent a document to a fictional printer. The
service reports a fault. The immediate message does not tell us which
revision was accepted, whether the driver was ready, or who owned the
operation. Those are separate questions, and each needs evidence.

Today we will examine how a system can describe an operation in an ordered
sequence of diagnostic records. We will then inspect a small binary trace
using a native C23 application. This is a learning exercise, not a control
programme for real interrupts or devices.

**On screen:** Display the fictional Notes window with one pending document,
then a brief error state. Replace the application view with an event table:
Attach, Ready, Observe, Checkpoint, Fault, Review, Stop, Release.

## 01:30–03:30 — Every record needs an identity

**Narration:**

A useful diagnostic record carries a sequence number, a logical tick, a
component identifier and a code. The sequence number tells us the order in
which records were written; a logical tick records a value in the simulated
timebase. Neither one alone tells us exactly when a physical device failed.

We also record the owner and its generation. A driver occupying slot one may
stop. A new driver can later reuse slot one, but it receives a different
generation. An old callback for generation one must not be allowed to operate
on generation two. This is why we treat a driver's lifetime as an identity
separate from its table index.

**On screen:** Display the
[driver lifecycle diagram](../../assets/diagrams/driver-lifetime-stages.svg).
Highlight the Attach and Release transitions. Show two owner-generation pairs
for the same slot.

## 03:30–05:30 — Why order is important

**Narration:**

Consider a record saying a service attempted revision 101. If we later find a
Fault record, we must not silently assume revision 101 completed. The service
might have accepted only revision 100. An attempted operation, a completed
operation and a durably stored operation are three different claims.

A recovery record is a statement that a review decision occurred. It is not
proof of physical repair. The hardware adapter still needs whatever checks
its protocol requires. Likewise, cancelling future work does not acknowledge
an already accepted interrupt.

**On screen:** Compare an attempted revision and a committed revision. Show the
earlier Service Recovery lab beside the new trace diagram.

## 05:30–08:00 — Understand the chain of digests

**Narration:**

The trace has a second property: every record stores a SHA-256 digest. For the
first record we calculate SHA-256 from a block of zero bytes followed by the
record's metadata. For the next record we calculate a new digest from the
previous digest and the next metadata. The digest of a later record therefore
depends on the bytes of the earlier records.

This is useful for detecting accidental changes. It is not proof that a trusted
party wrote the file. A person who can rewrite the complete file can calculate
a new chain. A real audit system needs additional provenance, durable storage,
access controls and an appropriate retention policy.

**On screen:** Display the
[digest-chain diagram](../../assets/diagrams/evidence-digest-chain.svg).
Follow the arrows from record one to record three. Then change a byte in the
first record and show why its original digest no longer matches.

## 08:00–10:45 — Run the native inspector

**Narration:**

Open the Umicom Applications checkout in PowerShell. We will use the existing
Framework-owned Umicom Education executable. First, we build and run its
regression tests. The first test writes a deterministic trace file; the
second test reads that file through the public command. This ordering matters
because the CLI test should never depend on an old file left by an earlier run.

**On screen:** Run:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" -R "evidence_trace" --output-on-failure
& ".\build\umicom-education\bin\umicom-education.exe" evidence-trace `
    --file ".\build\umicom-education\education-evidence-trace-test\fixture with spaces\driver evidence.evd"
```

**Narration:**

The inspector reports twenty records. It counts observations, checkpoints,
faults and recoveries. It also checks that the digest of each record matches
the previous one and that every state transition is permitted. We do not need
to execute a driver to review this teaching file.

## 10:45–13:15 — Test a malformed record

**Narration:**

A successful example is useful, but the negative tests teach more. Open
`test_evidence_trace.c`. Find the case where the digest chain is recomputed
after changing an owner or generation. That file may still be internally
consistent as a chain of bytes, but it represents an invalid state transition.
The inspector must reject it.

Notice that the parser preserves the caller's previous report when a later
record fails. It does not present partial results as a complete accepted
history. This is a general C23 design pattern: validate the whole proposed
change, then publish it once.

**On screen:** Show the case for a stale generation and the case for a wrong
checkpoint. Point out that both fail even after recalculating digests.

## 13:15–14:30 — Continue the lesson

**Narration:**

We have learned to ask better questions of a failure: who owned the work,
what was accepted, what was only attempted, and what can the recorded bytes
really establish? Next, we will build an in-memory diagnostic ring and compose
a driver lifecycle from reusable C23 services. We will also connect these
models to the real interrupt and driver boundaries in Umicom Kernel.

**On screen:** Display the lesson links and the Umicom Kernel repository.
Close with: **Service to Many Leads to Greatness.**
