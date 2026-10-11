# Episode 32 — How the Scheduler Gives Every Ready Task a Turn

**Duration:** 11–14 minutes  
**Learning pages:** [Scheduling](../../lessons/05-engineering/102-understand-round-robin-scheduling.md), [Wait and wake](../../lessons/05-engineering/103-wait-and-wake-without-spinning.md)  
**Code:** [Round-robin C23 laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/round-robin-scheduler)

## 00:00–01:30 — A practical question

**On screen:** Umicom Notes and a reporting application. The Notes task is saving a document. A monthly report is waiting to run.

**Narration:**

"When you have two applications open, you may see both making progress. One can save a document while another calculates a report. Does that mean a single processor core is executing both streams of instructions at exactly the same instant? No. One hardware thread runs one instruction stream at a time, and the operating system decides which runnable work should use it next.

"The component responsible for that choice is the scheduler. We will build a small version in C23, using Notes and Reports to illustrate the decisions. It will not control real processes. Its value is that every state and every decision is visible in a few source files."

## 01:30–03:30 — What ready, running and waiting mean

**On screen:** [Ready, Running and Waiting diagram](../../assets/diagrams/ready-waiting-scheduler.svg).

**Narration:**

"A ready task has useful work it can perform if a processor is available. A running task is the one the scheduler selected. A waiting task cannot continue yet. It might be waiting for a message, a timer or an input/output operation.

"Here is our ready queue. Notes is at the front, with Reports behind it. We select Notes and mark it Running. Reports stays Ready.

"Now imagine Notes needs confirmation that a document was saved. If no confirmation exists, repeatedly checking for it would waste processor time. The task changes to Waiting. Reports is still Ready, so the scheduler selects Reports next.

"When the save completion arrives, Notes can be made Ready again. Being ready is not the same as being running. Notes returns to the back of the queue. Reports does not lose the turn it already earned."

## 03:30–06:00 — Read the small C23 model

**On screen:** `labs/native/round-robin-scheduler/round_robin.h` and `round_robin.c`.

**Narration:**

"Open the public header. Here is our `BtbRoundRobin` type. It has eight task slots and eight positions for a ready queue. A slot records a generation number, a wait key and the task state. A ring index lets us move through the ready queue without shuffling every remaining task every time we select one.

"The first operation, `BtbRoundRobinInit`, places the model into a known empty state. `BtbRoundRobinAdmit` allocates a free slot and puts the task into Ready. `BtbRoundRobinNext` selects the oldest Ready task. If the queue is empty, it returns `BTB_SCHED_EMPTY`. It does not invent another task.

"Look at `BtbRoundRobinYield`. A Running task gives up its turn and returns to the back of Ready. Look at `BtbRoundRobinWait`: it makes that task Waiting and records a nonzero wait key. Later, `BtbRoundRobinWake` checks that the key matches before re-enqueuing the task.

"The most important design detail is not the eight-element array. It is the rule that an operation only makes an allowed state change. If the task is not Running, Yield cannot pretend it is. If a wake refers to the wrong key, Wake refuses the request."

## 06:00–08:40 — Build and test

**On screen:** PowerShell terminal. Type each command, waiting for results.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\round-robin-scheduler" `
    -B ".\output\learning-build\round-robin-scheduler" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\round-robin-scheduler" --parallel 2
ctest --test-dir ".\output\learning-build\round-robin-scheduler" --output-on-failure
& ".\output\learning-build\round-robin-scheduler\btb-round-robin.exe"
```

**Narration:**

"First, CMake creates the build description. Ninja then compiles the source into a static library and links the demonstration and its tests. CTest runs two independently registered checks.

"The first test verifies that Reports runs before Notes after Notes has been woken. The second test checks incorrect operations: an attempt to select a second task while one is already Running, an attempt to wake with the wrong key, and an attempt to admit a ninth task into eight full slots.

"A good automated test does more than show that the expected path succeeds. It should also prove that a refused operation leaves the existing state unchanged."

## 08:40–10:40 — A task handle is not its memory address

**On screen:** [Generation-tagged handles diagram](../../assets/diagrams/stale-task-handle.svg).

**Narration:**

"Imagine Notes ends, leaving an empty scheduler slot. Reports or another new task later uses the same slot. We cannot allow the old Notes handle to control the new task.

"Our handles contain the slot number and its generation. When a slot is reused, its generation changes. The old combination is now stale and is rejected. This illustrates a general idea used in operating systems and resource managers: identifying an object is not the same as knowing its memory address.

"Real kernels add more than generation checks. They enforce rights and ownership. A classroom handle is not a security capability simply because it is a 64-bit number."

## 10:40–13:00 — Look at the real Kernel and practise

**On screen:** [Umicom Kernel scheduler source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_scheduler.c); switch back to the teaching programme.

**Narration:**

"The actual Umicom Kernel has to preserve register frames, user task identity and address-space state. It interacts with trap handling and privileged operations that our hosted lesson does not execute. You can inspect those contracts in the Kernel repository, but you should not assume that passing our test proves the Kernel scheduler works on every computer.

"Try this exercise. Open the demonstration and predict which task runs after `BtbRoundRobinWake`. Then find the test that expects `BTB_SCHED_EMPTY`. Explain why an empty Ready queue does not necessarily mean the system has no live tasks.

"The next lesson connects the scheduler to a copied-message queue. We will see exactly how a Notes service waits without burning processor time, and why cancellation must not silently delete an already accepted message. The full source and the illustrated chapters are available in the Bits2Banking repository."
