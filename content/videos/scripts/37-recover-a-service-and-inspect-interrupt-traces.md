# Episode 37 — Recover a service and inspect interrupt ownership traces

**Duration:** approximately 14–18 minutes, including code walkthroughs and tests  
**Reading:** [Lesson 114](../../lessons/05-engineering/114-restore-a-service-after-failure.md), [Lesson 115](../../lessons/05-engineering/115-inspect-interrupt-ownership-traces.md), [Lesson 116](../../lessons/06-umicom/116-read-umicom-kernel-interrupt-and-recovery.md)  
**Laboratories:** [Service recovery](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/service-recovery)

## 00:00–02:30 — A failure between beginning and committing

**On screen:** A Notes document has revision 1 saved. A processing panel shows revision 2 marked In Progress.

**Narration:** “Suppose a Notes service has completed its first request. The service records revision 1 as accepted. It now starts revision 2. But before revision 2 is acknowledged, a fault occurs. The important thing is that we must not call revision 2 completed merely because it began. We also must not lose the knowledge that revision 1 succeeded.”

“Reliable applications need to distinguish accepted work from work in progress. This is the basis of many transaction, recovery and audit systems. Today our experiment is a small C23 service model; there is no database, disk journal or real payment. That limitation is deliberate. We want to see the precise state transitions before adding more complex storage.”

## 02:30–05:25 — One source model, a composed service

**On screen:** Show [the service recovery diagram](../../assets/diagrams/service-checkpoint-recovery.svg). Then display the `service-recovery/CMakeLists.txt` file.

**Narration:** “We already built a fictional interrupt-source owner. We should not write its state machine again for the Notes service. Instead, our new library composes the same C23 ownership source. The CMake project adds the existing interrupt-ownership directory and links against its library. This makes it easy to see which component owns the decision about a lease and which one owns the Notes service’s accepted revision.”

“Start the service. Its owner identity is 7. Claim one source and arm it. Begin revision 1. On Commit, the source is acknowledged and its handling interval ends. Only after those checks does the Notes service update its accepted revision and prepare for another operation. Now Begin revision 2, but call Fault rather than Commit. The in-progress number is still 2, while the accepted number stays at 1.”

**On screen:** Show `BtbServiceFault()` and the test which refuses a commit after fault.

**Narration:** “The refusal is the safety feature. A faulted operation must not be silently accepted. Recover explicitly clears the in-flight request while retaining revision 1. A caller may start revision 2 again, but only as a new deliberate action.”

## 05:25–08:15 — Build and inspect expected results

**Demonstration:** Run the laboratory with the Windows development toolchain:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\service-recovery" `
    -B ".\output\learning-build\service-recovery" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\service-recovery" --parallel 2
ctest --test-dir ".\output\learning-build\service-recovery" --output-on-failure
& ".\output\learning-build\service-recovery\btb-service-recovery.exe"
```

**Narration:** “Two tests exercise the demonstration and refusal rules. Notice how a duplicate Begin is refused while a request is in flight. Stop also fails until the service returns to a safe, quiescent state. After a fault, Recover does not immediately replay work. The demonstration explicitly retries revision 2 and reaches a last accepted revision of 2.”

“An important warning: our accepted number is only in RAM. A real filesystem or financial system needs durable storage and a protocol for incomplete writes. This exercise is not a crash-consistent journal. It is a first step in understanding one.”

## 08:15–11:25 — Read a reproducible native trace

**On screen:** Show the file header table from [Lesson 115](../../lessons/05-engineering/115-inspect-interrupt-ownership-traces.md).

**Narration:** “We can now describe an interrupt-source sequence as records. Umicom Framework has a C23 teaching inspector which reads a defined format. The header includes a magic sequence, version and record count. Each 32-byte record identifies one action, source, owner, generation and logical tick. The parser refuses unexpected bytes and impossible changes of state.”

“Because each field has a fixed width, a corrupt record cannot move the next record’s starting position. The source number is bounded; the owner must match the currently leased source; a new generation must be greater than the earlier one. A parser can therefore report precisely what it accepts rather than guessing a corrected interpretation.”

**Demonstration:** In Umicom Applications, after building its education tools:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
ctest --test-dir ".\build\umicom-education" --output-on-failure
$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education interrupt-trace --file `
    ".\build\umicom-education\education-interrupt-trace-test\fixture with spaces\owned interrupt.irq"
```

**Narration:** “The output should report 20 records. We see three claims, four arms, three handler entries, two acknowledgements, one cancellation, one fault, one explicit recovery and three releases. There were two simultaneously owned sources at the high-water mark and none left at the end.”

## 11:25–14:40 — Why a corrupted trace must not become evidence

**On screen:** Show `test_interrupt_trace.c`, then highlight the checks for duplicate generation, wrong owner, cancellation after ENTER, and a fault without a code.

**Narration:** “We test more than successful parsing. We modify the trace to claim an old generation. We attempt to acknowledge before a handler has entered. We try to cancel a handler already in progress. Each must fail. We also repeatedly change individual bytes and run the inspector under ordinary C23 tests and sanitizer configurations.”

“The C23 parser builds a local report. It assigns the report to the caller only after every record is valid. If the last record is malformed, the caller’s previous report stays unchanged. This is a general design pattern you can use when decoding configuration, network messages or stored financial records: validate first, publish second.”

## 14:40–End — Compare with the genuine Kernel

**On screen:** [Umicom Kernel interrupts guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/INTERRUPT_OWNERSHIP.md), `kernel/interrupts.c`, `kernel/trap_guard.c` and `kernel/user_ipc.c`.

**Narration:** “Our trace is not a recording of real CPU interrupts. The actual Kernel controls machine-level state and must defend privilege, register frames and resource ownership. Its interrupt controller is a trusted, single-hart service. Its guarded trap path may require an emergency stop when the saved machine state is corrupt. A program cannot prove that a damaged register frame is safe just by replaying a file of expected events.”

“Remember the bigger lesson: before making a program more powerful, make its responsibilities explicit. Decide who owns a resource, which state transition is legal, when work becomes accepted, and which errors must stop normal progress. Those principles connect a small Notes application to the engineering of operating systems, databases and financial services.”

**End screen:** [Lessons 114–116](../../lessons/05-engineering/114-restore-a-service-after-failure.md) · [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel) · [Bits2Banking](https://github.com/umicom-foundation/Bits2Banking).
