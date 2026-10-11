# Episode 35 — Event signals, timeouts and Umicom Kernel

**Duration:** 15–19 minutes  
**Reading:** [Lessons 108–111](../../lessons/05-engineering/108-event-signals-waits-and-recovery.md)  
**Source:** [`labs/native/timed-service-waits`](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/timed-service-waits)

## 00:00–02:00 — A waiting Notes task

**On screen:** A Notes window, a background indexing service, and a diagram showing Ready → Running → Waiting.

**Narration:** “Suppose the Notes application sends a request to a service and then waits for a reply. Repeating a check thousands of times while the queue is empty wastes processor time. In the previous course we gave the scheduler a Waiting state so it could run another task. Today we will add an event and a deadline. One can complete the operation early, while the other prevents an indefinite wait. The challenge is to make these outcomes consistent when they happen very close together.”

## 02:00–04:30 — An event notification is not a message

**On screen:** [Event awards diagram](../../assets/diagrams/event-signal-awards.svg). Highlight manual-reset and auto-reset cases.

**Narration:** “An event is a piece of remembered state. A manual-reset event stays signalled until its owner clears it. An auto-reset event can grant a single waiting operation or retain one credit. Repeated signals may combine into one credit. That does not mean the event holds three messages or that it has reserved three queue slots. The queue owns accepted data. The event simply tells the receiver that something may have changed. After waking, the receiver checks the queue again. This is the difference between notification and authority.”

**Narration:** “Now consider a lost-wake race. The receiver checks an empty queue, the sender adds a message and signals, but the receiver only begins waiting afterwards. If that signal was not remembered and the wait registration was not protected, the receiver could sleep even though a message is waiting. Our classroom programme runs one owner at a time, so it has no concurrent interruption between the check and the wait. Umicom Kernel uses a separate, documented serialisation contract. We must not mistake either design for a general multi-core locking solution.”

## 04:30–07:30 — Reuse existing C23 components

**On screen:** `timed-service-waits/CMakeLists.txt` and `service.c`.

**Narration:** “We already have two tested components: a round-robin scheduler and a checked logical timer. The service should compose them rather than copy their algorithms. The build file compiles the same `round_robin.c` and `deadline.c`. The new `service.c` remembers which Notes task is waiting, which event key belongs to it, and whether the final outcome was a signal, a timeout or cancellation. The service borrows pointers to the scheduler and clock; it does not own or destroy them.”

**On screen:** Show `BtbTimedWaitStart()` validating the deadline before calling `BtbRoundRobinWait()`.

**Narration:** “Validation order matters. If the clock is already at the maximum 64-bit value, adding one more tick is impossible. The service returns an overflow error before changing the scheduler. The Notes task remains Running, and the test can observe that fact. Publishing half of a wait would be a subtle state corruption.”

## 07:30–11:00 — Three outcomes and a tie

**On screen:** Timeline first signal at 104, then timeout at 105, then cancellation while waiting.

**Narration:** “The task starts waiting at tick 100 with a five-tick deadline. When its matching event arrives at 104, the wait completes successfully and the task becomes Ready. It is not automatically Running. The scheduler selects it on a later dispatch. In the second scenario, the event arrives exactly at 105. Our published rule says the timeout wins at the deadline. The event cannot silently overrule that outcome. The explicit pump completes the timeout, records it and makes the task Ready. In the third scenario, an infinite wait is cancelled. The scheduler stops that task; an old call cannot treat the stopped task as the next runnable one.”

**Demonstration:** Build and run the project:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\timed-service-waits" `
    -B ".\output\learning-build\timed-service-waits" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\timed-service-waits" --parallel 2
ctest --test-dir ".\output\learning-build\timed-service-waits" --output-on-failure
& ".\output\learning-build\timed-service-waits\btb-timed-service.exe"
```

**Narration:** “Three tests cover an early event, an exact-deadline timeout and a cancelled wait. The demonstration completes one Notes timeout at tick 105 and then shows a separate scheduler dispatch. A reliable programme reports each outcome, rather than silently retrying until something happens.”

## 11:00–14:00 — Read the native timer trace

**On screen:** Framework command `umicom-education timer-trace --file ...`.

**Narration:** “Tests can also leave evidence. The Framework-owned timer-trace inspector reads a small binary file. Every record has an ordinal, an event type, a task identity, an event key, the logical tick and, for a wait, an optional finite interval. The file is versioned and bounded. The inspector rejects time reversal, invented identities, mismatched keys, overflow and late signals. Crucially, a rejected file does not partially overwrite the previous report.”

**Demonstration:** Run the education CTest suite, then inspect the generated `clock events.tmr` fixture using the commands in [Lesson 110](../../lessons/05-engineering/110-inspect-a-timer-trace-in-c23.md). Read the output aloud: four waits, one signal, two timeouts and one cancellation.

## 14:00–17:00 — Where Umicom Kernel begins

**On screen:** [Kernel boundary diagram](../../assets/diagrams/clock-scheduler-kernel-boundary.svg), then the actual source links.

**Narration:** “The classroom timer never installs a hardware interrupt. Real Umicom Kernel code must preserve registers when a trap occurs. Its RISC-V Assembly entry handles the privileged mechanism, and C23 code handles policy and ownership. The scheduler retains the user task's continuation so it can resume rather than restart. The event layer records completion before waking a blocked thread. Those are the responsibilities we must understand before treating a simulation as a real operating system service.”

**On screen:** Show source references to [`arch/riscv64/trap.S`](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap.S), [`kernel/user_scheduler.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_scheduler.c) and [`kernel/events.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/events.c).

**Narration:** “Compare the existing Kernel documentation with our laboratory. Note where interrupts are disabled, how ownership is checked and how a result is recorded before a task is runnable. These are the foundations of controlled concurrency and recovery. The next learning stage will study interrupt ownership, failure handling and retained service state.”

**End screen:** [Lessons 108–111](../../lessons/05-engineering/108-event-signals-waits-and-recovery.md), [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel) and [Bits2Banking](https://github.com/umicom-foundation/Bits2Banking).
