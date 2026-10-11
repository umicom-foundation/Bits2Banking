# Episode 36 — Who owns a hardware interrupt?

**Duration:** approximately 13–17 minutes, including practical demonstrations  
**Reading:** [Lesson 112](../../lessons/05-engineering/112-interrupt-ownership-and-critical-sections.md) and [Lesson 113](../../lessons/05-engineering/113-cancellation-is-not-acknowledgement.md)  
**Laboratory:** [Interrupt ownership](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/interrupt-ownership)

## 00:00–01:45 — A timer shared by two services

**On screen:** The Umicom logo, a Notes application window and two fictional services: Notes indexing and a background reporter. A timer appears between them.

**Narration:** “A computer has many things happening at once. A program may be saving a note, updating an index and checking the time. The operating system decides when user instructions run and how external events are handled. We have already explored task scheduling and timeouts. Today we will investigate a more subtle question: who is allowed to control the timer that generates an interrupt?”

“Imagine that the Notes indexer changes the timer and the reporting service changes it again. One of them expects the timer to fire in five milliseconds. The other expects fifty. The hardware has one set of active registers; both programs cannot simply assume that its current settings belong to them. We need a clearly identified owner. We also need to distinguish a timer being masked from an interrupt being acknowledged.”

## 01:45–04:00 — Interrupts, sources and protected work

**On screen:** [Interrupt ownership diagram](../../assets/diagrams/interrupt-source-ownership.svg).

**Narration:** “An interrupt is a request for processor attention. A timer is one source. In a typical operating-system design, hardware delivers an interrupt to a privileged handler. That handler executes with greater authority than an ordinary user application. It must be careful: changing the wrong register can affect a completely unrelated task.”

“A critical section protects a small sequence of operations. Suppose the outer function temporarily disables interrupt delivery and calls a helper. The helper enters a second critical section, finishes, and leaves. If the helper blindly enables interrupts on its way out, it ends the outer function’s protection too early. The correct design remembers the previous state and restores it only when the matching outermost owner leaves.”

“Ownership goes further. One service can acquire a lease for a particular interrupt source. Another service cannot simply take that source away. Even an existing lease does not mean the owner may ignore pending device work, execute in an unsafe context or bypass the hardware’s own rules.”

## 04:00–06:20 — Build the ownership model

**On screen:** Show `owner.h`, `owner.c` and `CMakeLists.txt` under `labs/native/interrupt-ownership`.

**Narration:** “Our classroom implementation is written in C23. It is a state machine, not a device driver. It deliberately never reads a control register, masks a real interrupt or changes the machine’s privilege level. That makes it safe to explore on an ordinary computer while we learn the vocabulary used by the actual Kernel.”

“The first state is Free. A successful Claim assigns an owner and an increasing generation number. Arm means the model is ready for a fictional interrupt. Enter records that handling has begun. Acknowledge marks the event acknowledged; Return completes the handling interval. The source can now be released.”

“Notice the lease token. It has a source number, an owner identity and a generation. The token itself is not a password. It is evidence that must be checked against the live domain. If source 1 is released and later given to a different owner, the old token must not suddenly work again. The increasing generation helps detect that mistake.”

**Demonstration:** Execute from PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\interrupt-ownership" `
    -B ".\output\learning-build\interrupt-ownership" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\interrupt-ownership" --parallel 2
ctest --test-dir ".\output\learning-build\interrupt-ownership" --output-on-failure
```

**Narration:** “The demonstration follows a normal ownership path. The contract test then challenges it: what if a caller tries to release the source while armed? What if another owner uses the same token? What if the generation is old? We expect refusals, not silent state changes.”

## 06:20–09:05 — Cancellation is not acknowledgement

**On screen:** [Cancellation diagram](../../assets/diagrams/cancel-acknowledge-recovery.svg).

**Narration:** “This distinction appears in many systems. Cancelling a request to save a document is not the same as undoing a write that already reached the filesystem. Cancelling a pending financial instruction is not the same as reversing a completed ledger entry. Likewise, cancelling an armed interrupt source before its handler begins is different from acknowledging an event the handler has already accepted.”

“Our lab allows Cancel from Armed. It refuses Cancel once the handler has entered. Acknowledgement and Return are separate steps, because completing one does not prove that the other is safe. When a fault is recorded, the fictional source enters a special Faulted state. The ordinary Release operation is refused until a separate review-and-recover transition occurs.”

“Now think about real hardware. A damaged trap frame, a pending device condition or a privilege-state error cannot be fixed merely by changing an enum value. The real Kernel may have to stop instead of trying to resume. Our classroom transition is deliberately narrower than real recovery.”

## 09:05–12:15 — Read the Umicom Kernel implementation

**On screen:** Show the authentic files in the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel): `docs/INTERRUPT_OWNERSHIP.md`, `include/umicom/kernel/interrupts.h`, `kernel/interrupts.c`, and `arch/riscv64/trap.S`.

**Narration:** “In the RISC-V privileged architecture, the MIE bit in `mstatus` controls global machine-interrupt delivery. The `mie` register enables specific machine interrupt sources. Those are not the same as a device’s pending condition. The Kernel’s ownership guide explains why capturing and clearing MIE must be performed as one appropriate register operation and why restoring an old, complete `mstatus` word could overwrite other control state.”

“Open the public header and find the critical-section Enter and Leave operations. Notice how the API names ownership and tokens explicitly. In the C implementation, read the checks performed before a source is acquired or an old section is restored. The interface documents a trusted, single-hart controller, not a generic multi-core locking mechanism.”

“Next open `arch/riscv64/trap.S`. The Assembly establishes the privileged entry mechanism and saves the register frame. Ordinary C cannot perform that first machine-state transition by calling an interrupt handler as though it were another application function. C23 can then inspect and apply policy to a validated frame. Assembly and C have distinct responsibilities.”

## 12:15–End — Questions and next lesson

**On screen:** Three questions: “Who owns the source?”, “Has handling started?”, “Can old ownership be reused?”

**Narration:** “A safe system does more than make normal work succeed. It prevents an old caller from changing a new owner’s state. It refuses cancellation after a handler has already accepted work. It records faults instead of hiding them, and it restores only the control state which the caller actually owns.”

“Work through the tests and trace one failed cancellation. Then follow the real Kernel source and identify the boundary between privileged Assembly and C23. In our next episode we will add a fictional Notes service checkpoint, preserve accepted work across a simulated fault, and inspect a binary trace using the Framework-owned education command.”

**End screen:** [Lesson 112](../../lessons/05-engineering/112-interrupt-ownership-and-critical-sections.md) · [Lesson 113](../../lessons/05-engineering/113-cancellation-is-not-acknowledgement.md) · [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel).
