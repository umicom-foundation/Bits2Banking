# Episode 39 — Driver lifetimes and retained evidence

**Approximate duration:** 14–18 minutes  
**Companion lessons:** [118. Driver lifecycle](../../lessons/05-engineering/118-build-a-driver-lifecycle.md), [119. Diagnostic ring](../../lessons/05-engineering/119-keep-diagnostics-in-a-bounded-ring.md), [121. Kernel driver boundaries](../../lessons/06-umicom/121-kernel-driver-and-interrupt-boundaries.md)

## 00:00–02:00 — One device, one owner

**Narration:**

A driver acts on behalf of a device or service. It does not become safe simply
because its initialisation function returned. Its lifetime includes acquiring
resources, becoming ready, completing requests, handling faults and releasing
those resources in a controlled order.

In this episode we will build a fictional driver by composing two C23 libraries
we already developed. We will not duplicate an interrupt-controller
implementation, and we will not interact with real hardware. The purpose is
to understand the architectural contract before examining Kernel code.

**On screen:** Display the ownership diagram with Attach and Ready highlighted.
Identify the existing `interrupt-ownership` and `service-recovery` directories.

## 02:00–04:30 — Follow a single revision through the service

**Narration:**

The example begins by accepting revision 100 in a fictional Notes service.
Revision 101 starts but then fails. If we inspect the committed value it must
still be 100. A request that began is not necessarily a request that completed.

Now try to stop the driver while its source remains faulted. The model refuses
that transition. Before it can stop, a caller must explicitly review the
incomplete revision and recover the teaching service. It may then retry 101.
Only a completed retry advances the committed revision to 101.

**On screen:** Follow `BtbDriverComplete`, `BtbDriverFail`,
`BtbDriverReviewAndRecover` and `BtbDriverStop` in `driver.c`. Highlight the
checks that return `BTB_IRQ_WRONG_STAGE`.

## 04:30–07:30 — Build and test the lifecycle

**On screen:** Run:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\driver-lifecycle" `
    -B ".\output\learning-build\driver-lifecycle" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\driver-lifecycle" --parallel 2
ctest --test-dir ".\output\learning-build\driver-lifecycle" --output-on-failure
& ".\output\learning-build\driver-lifecycle\btb-driver-lifecycle.exe"
```

**Narration:**

Notice that the build includes tests from the earlier libraries. The
`service-recovery` target already composes interrupt ownership, so the new
project links to it. A new component should reuse a proven contract rather
than copy its implementation and create another source of truth.

The demonstration reports an accepted revision of 101 and one reviewed fault.
Both values are in memory. They do not prove durable persistence or an actual
hardware repair.

## 07:30–10:30 — Store diagnostics without unbounded memory growth

**Narration:**

A running service can produce more diagnostic messages than an application
should keep in memory. We will use a ring buffer with eight entries. The ring
stores copied integer records. Each record contains a sequence number, logical
tick, source and code.

After ten events, only eight remain. The first two have been overwritten.
The program records that loss. A diagnostic snapshot contains values copied
from the ring, not pointers into a live mutable array.

**On screen:** Show the
[ring-buffer diagram](../../assets/diagrams/bounded-ring-versus-retained-file.svg).
Run the following commands:

```powershell
cmake -S ".\labs\native\diagnostic-ring" `
    -B ".\output\learning-build\diagnostic-ring" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\diagnostic-ring" --parallel 2
ctest --test-dir ".\output\learning-build\diagnostic-ring" --output-on-failure
& ".\output\learning-build\diagnostic-ring\btb-diagnostic-ring.exe"
```

**Narration:**

The expected result is eight retained entries, two overwritten entries, and
sequence three as the first retained event. A fixed-size buffer gives bounded
RAM usage, but it does not preserve everything that happened. If the machine
loses power, this in-memory ring disappears.

## 10:30–13:00 — What would real retained evidence require?

**Narration:**

To preserve diagnostics beyond a process lifetime, a production service needs
more than a ring: explicit persistent storage, write failure handling,
retention policy, integrity checks and an appropriate provenance model.

We studied a SHA-256-chained teaching file in the previous episode. That file
can reveal accidental damage, but its chain is not a trusted signature.
The ring also has a dropped counter. These properties solve different
problems: bounded runtime memory is not durable history, and a matching digest
is not authentication.

**On screen:** Put the two designs side by side. Label them **bounded
in-memory diagnostics** and **validated classroom trace file**. Under both,
show the missing production requirements.

## 13:00–16:30 — Connect the model to Umicom Kernel

**Narration:**

Open the Umicom Kernel source. In `arch/riscv64/trap.S`, the Assembly entry
saves the processor context before C23 can inspect the trap. In
`kernel/interrupts.c`, the trusted C implementation coordinates machine
interrupt enable state, nested critical sections and source leases.

These are real privileged components. Our classroom driver is not a substitute
for them. Its value is educational: we can inspect a small state machine,
trigger deliberate failures and prove its refusal rules without touching a
processor register.

The Kernel's source comments and documentation state important limits: the
interrupt-ownership controller is scoped to one hart and is not a general SMP
lock. Learners should read those contracts before suggesting changes to a
production driver.

**On screen:** Open these authoritative files:

- [RISC-V trap entry](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap.S)
- [Interrupt ownership](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/interrupts.c)
- [Driver example: VirtIO block](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtio_block.c)

## 16:30–17:30 — What to practise next

**Narration:**

Run the two laboratory test suites. Change one fictional revision number,
then change a diagnostic-ring capacity and update the expected result. Explain
why neither test should require a running Kernel. Next we will study how
explicit driver interfaces translate validated requests into device I/O, and
how those requests are cancelled or completed safely.

**On screen:** Display the Bits2Banking website and relevant GitHub
repositories. End with **We Value Each Other and Together Everyone Achieves
More.**
