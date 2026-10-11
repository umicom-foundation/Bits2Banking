# 111. Follow timer interrupts and event delivery through Umicom Kernel

The previous four lessons used a single-threaded, logical clock and simulated tasks. The real Umicom Kernel works closer to hardware. In its RISC-V64 research configuration, a timer can interrupt a running user programme, and the Kernel must preserve execution state before selecting further work.

The crucial difference is **ownership**: Assembly handles the machine-level entry and exit mechanism; the C23 Kernel code decides how tasks, events and messages change state. The educational `umicom-education timer-trace` command merely reads fictional records; it neither programs a device nor intercepts an interrupt.

## 1. Find the Kernel source

Open the following files in the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel):

| File | What to examine |
| --- | --- |
| [`arch/riscv64/trap.S`](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap.S) | Saving registers, entering the trap dispatcher and returning with `mret` |
| [`kernel/user_scheduler.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_scheduler.c) | Task lifetime and choosing a runnable continuation |
| [`kernel/events.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/events.c) | Remembered signals, wait registration and completion before wake |
| [`kernel/user_ipc.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_ipc.c) | Blocking message operations and the lifetime of copied pending data |

Read the accompanying guides, especially [Traps and Timer](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/TRAPS_AND_TIMER.md), [Timer-Driven User Scheduling](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/TIMER_DRIVEN_USER_SCHEDULING.md) and [Events and Wait-Any](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/EVENTS_AND_WAIT_ANY.md).

## 2. What happens when the timer interrupts execution?

A timer interrupt is not an ordinary C function call. RISC-V hardware records the interrupted instruction address and cause in privileged control/status registers and transfers control to the configured trap vector. It does **not** automatically save all of the application’s working registers.

The privileged Assembly entry must preserve the required registers and establish a safe Kernel context before calling C23. When processing is complete, the correct interrupted continuation can eventually be restored. A timer stop is not automatically the end of a programme.

![The privileged timer boundary and reusable scheduler](../../assets/diagrams/clock-scheduler-kernel-boundary.svg)

Review the `mtvec`, `mepc`, `mcause` and `mstatus` descriptions in the Kernel's traps guide. These registers belong to the hardware execution model, not to the C23 timer laboratory.

## 3. Separating a timer stop from a process exit

In the Kernel's existing resumable user-scheduling path, a timer can pause a user task. Its program counter, integer registers and private address-space ownership are retained so the same task can continue later. The scheduler selects the next eligible task using Kernel-owned records. Re-entering the executable's entry point would **restart the programme**, so it is not how a paused task resumes.

The current documented scheduling configuration describes serial machine-mode Kernel operations on its selected hart. This is not evidence of general-purpose multicore scheduling, a complete POSIX implementation or hardware-independent operating-system support.

## 4. Events and blocked IPC

The event layer remembers signals. A manual-reset event can stay signalled until reset. An auto-reset event can award one waiter or keep one credit. Neither mode substitutes for the message queue that owns copied payloads.

For a blocked receive, the Kernel retains a stable task record and a pending operation. It does not keep a pointer to a temporary trap stack whose lifetime has ended. On completion, the result is written into retained state **before** the task becomes runnable. This ordering protects a task which cannot execute immediately.

Real user buffers require memory checks. The Kernel's [`message_service.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_service.c) and [`user_memory.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c) demonstrate why a user-space address cannot simply be treated as a trusted machine-mode pointer.

## 5. Compare the teaching and Kernel boundaries

| The classroom C23 model | Actual Umicom Kernel responsibility |
| --- | --- |
| A caller explicitly advances a logical clock | Hardware/platform timer readings and interrupts |
| `BtbRoundRobinNext()` selects a fictional task | The Kernel restores a protected continuation |
| `BtbTimedWaitPump()` marks a task Ready | A Kernel wait is completed and its saved frame updated |
| A synthetic trace shows SIGNAL, CANCEL and ADVANCE | Privileged event and service code enforces ownership and admission |
| `umicom-education timer-trace` reads a local file | Kernel validation proves live state and hardware behaviour on the qualified QEMU target |

The educational components should **never** be linked into the kernel as replacements for its own timer, scheduler or IPC mechanisms.

## 6. Examine the actual RISC-V source

In `arch/riscv64/trap.S`, locate the instruction which installs the trap vector and identify where the saved frame is established. Find the instruction used to return from a machine trap. In `kernel/user_scheduler.c`, identify the task's retained state and the checks performed before resuming. In `kernel/events.c`, locate the rule that a completed outcome is published before a waiting thread is woken.

For an optional guest run, follow the [Kernel's normal build and test guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md). Use its actual `riscv64-clang-debug` preset and documented QEMU invocation. A successful C23 teaching-lab test is **not** evidence that QEMU boot or real interrupt handling passed.

**Practise:** Explain why the Assembly trap handler saves registers before calling the C dispatcher. Then explain why the event owner must not write its result into a previously abandoned user stack. Finally, identify the component which owns each of: the message bytes, the task's saved continuation, the timeout decision and the ready queue.

Continue with the next course: interrupt ownership, fault recovery and the boundaries of safe Kernel services.
