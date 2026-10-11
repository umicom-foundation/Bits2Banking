# 95. Model a process lifecycle in C23

A modern operating system runs many programs. It needs to remember which processes can run, which are waiting for an event and which have finished. A **state machine** gives those states and allowed changes precise names.

Our example is a fictional worker inside **Umicom Notes**. The example is not a process launcher; it helps us reason about the rules a real kernel needs.

## 1. Meet the states

| State | Meaning |
| --- | --- |
| `NEW` | A process record has been created but not admitted for scheduling |
| `READY` | It may run when the scheduler selects it |
| `RUNNING` | It is selected as running in the teaching model |
| `WAITING` | It cannot proceed until an event occurs |
| `TERMINATED` | It has finished and cannot be restarted through this record |

The model permits:

```text
NEW --admit--> READY --dispatch--> RUNNING
RUNNING --yield--> READY
RUNNING --wait--> WAITING --wake--> READY
RUNNING --exit--> TERMINATED
```

A direct `NEW → RUNNING` change is refused because the required admission and dispatch steps have not occurred.

## 2. Understand the C23 data structure

The laboratory stores a process identifier, revision number, state and exit code:

```c
typedef struct BtbProcess {
    uint32_t identifier;
    uint32_t revision;
    BtbProcessState state;
    int exitCode;
} BtbProcess;
```

The identifier names the fictional process record. The **revision** increases after each successful transition. It helps us detect stale state and prevents silently treating an old record as a current one.

A failed transition must leave the structure unchanged. To achieve that, the implementation first decides whether the requested transition is legal, prepares a copy of the new state and publishes it only after all checks pass.

## 3. Compile the application and its tests

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\process-lifecycle" -B ".\output\learning-build\process-lifecycle" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\process-lifecycle" --parallel 2
ctest --test-dir ".\output\learning-build\process-lifecycle" --output-on-failure
& ".\output\learning-build\process-lifecycle\btb-process-demo.exe"
```

Both tests should pass. The demonstration prints a sequence that begins at `revision 1: new` and ends at `revision 7: terminated`.

## 4. Investigate a refused transition

Open `labs/native/process-lifecycle/test_process.c`. Find the test that attempts to exit directly from the `NEW` state. This operation returns `BTB_PROCESS_ILLEGAL_TRANSITION` and leaves the previous bytes of the process record unchanged.

Now find the revision-overflow test. It sets the revision to the largest 32-bit unsigned value and attempts a legal state transition. The operation must return `BTB_PROCESS_REVISION_EXHAUSTED` rather than wrap to zero. This matters because a wrapped revision could be mistaken for new state.

## 5. Connect the lesson to Umicom Kernel

The real [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel) has process registry, supervisor and scheduling implementations. Start with:

- [process_registry.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/process_registry.c) for process identity and records;
- [process_supervisor.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/process_supervisor.c) for supervision;
- [user_scheduler.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_scheduler.c) for user scheduling.

A real scheduler must save and restore CPU state, control privileges, account for time, cooperate with interrupts and manage separate address spaces. None of these privileged operations happens in the lesson program.

## 6. Practise

Add a test for the transition `RUNNING → READY` using the `BTB_EVENT_YIELD` event. Confirm that the revision increases exactly once. Then try `READY → WAITING` without dispatching first and explain why that transition is refused.

Next: [Lesson 96](../06-umicom/96-riscv-privilege-and-trap-boundaries.md) connects process and page faults to actual RISC-V privilege and trap instructions.
