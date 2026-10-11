# Episode 33 — Waiting for Messages, Closing Services and Reading Umicom Kernel

**Duration:** 12–16 minutes  
**Learning pages:** [Wait and wake](../../lessons/05-engineering/103-wait-and-wake-without-spinning.md), [Service lifetimes](../../lessons/05-engineering/104-task-handles-and-service-lifetimes.md), [Kernel source](../../lessons/06-umicom/106-follow-umicom-kernel-scheduler-and-ipc.md)  
**Code:** [Blocking IPC C23 laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/blocking-ipc-lifetimes)

## 00:00–02:00 — The Notes service has nothing to receive

**On screen:** Draw a Notes service and an empty channel. Show the receiver in Waiting and Reports in Ready.

**Narration:**

"Our Notes application has sent work to a service and expects a reply. At the moment, that reply has not arrived. We can write a loop that checks the queue constantly. But on a computer with other work to do, that repeated checking is wasteful.

"A better arrangement lets Notes become Waiting. The processor can do useful work elsewhere. When a message reaches the queue, Notes becomes Ready again, and the scheduler eventually allows it to run.

"A key distinction will guide us throughout this lesson: the scheduler owns whether a task may run. The message channel owns the bytes sent to a receiver. The service connects these two components, but should not become the owner of everything."

## 02:00–04:30 — Separate the three owners

**On screen:** [Copied-message ownership diagram](../../assets/diagrams/blocking-ipc-wakeup.svg).

**Narration:**

"Here the sender has a text buffer containing Draft stored. The sender calls the bounded channel's send operation. On success, the channel makes its own copy. The sender can now change its original buffer without changing the queued message.

"The receiver has a task handle. It belongs to a scheduler. The service adapter holds borrowed references to the channel and scheduler, but does not allocate either one. That means the service must not free those objects just because its own work ends.

"This is why we use the existing C23 modules from earlier lessons. `bounded-channel/channel.c` already implements the small copy-owning FIFO. `round-robin-scheduler/round_robin.c` already implements the ready and waiting states. We link those libraries to a new `session.c` adapter. We do not copy the old logic into the adapter and create a competing implementation."

## 04:30–07:00 — Walk through the wait-to-wake operation

**On screen:** `session.c`, focusing on `BtbSessionWaitForMessage`, `BtbSessionPoll` and `BtbSessionReceive`.

**Narration:**

"At the start, the receiver is Running and the queue is empty. `BtbSessionWaitForMessage` checks whether there is already a message. If there isn't, it registers a wait with a key. The scheduler removes that task from the set of runnable work.

"Later, the sender calls `BtbSessionSend`. The channel accepts and copies the complete payload. `BtbSessionPoll` sees a message available and asks the scheduler to wake the waiting task.

"Notice that Wake is not Dispatch. The task has become Ready. It must still wait its turn until the scheduler chooses it. After selection, the receiver supplies a buffer and `BtbSessionReceive` copies the message out of the channel.

"What if the receiver's buffer is too short? The channel refuses the receive. It does not consume half of a message. The test deliberately tries an undersized destination, confirms that the message is still queued, and then retries with enough capacity."

## 07:00–09:45 — Build and test cancellation

**On screen:** PowerShell terminal.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\blocking-ipc-lifetimes" `
    -B ".\output\learning-build\blocking-ipc-lifetimes" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\blocking-ipc-lifetimes" --parallel 2
ctest --test-dir ".\output\learning-build\blocking-ipc-lifetimes" --output-on-failure
& ".\output\learning-build\blocking-ipc-lifetimes\btb-blocking-ipc.exe"
```

**Narration:**

"These tests cover two different outcomes: successful delivery, and cancellation while a receiver is waiting. Let's inspect the cancellation test.

"The service begins waiting. The sender puts a message in the channel. Before the receiving task resumes, the service closes. The pending wait is cancelled, and the scheduler invalidates that task. Yet the queued message remains intact because the channel is owned by somebody else.

"Cancellation does not mean history disappears. A send already accepted is not undone just because its original receiver closed. A safe implementation has to decide who owns the accepted work and which component may release it."

## 09:45–12:00 — Trace the events without running a kernel

**On screen:** `umicom-education schedule-trace --file ...` and a diagram of ordered events.

**Narration:**

"A trace lets us review state changes. Our native Framework command reads a little-endian classroom file containing admit, dispatch, yield, wait, wake, exit and cancellation records. Every event has a task ID and a logical tick. A wait and its matching wake share a key.

"The parser checks that an event is allowed in the state it describes. It refuses an attempt to dispatch a task that is not at the front of the Ready queue. It refuses a wake that names the wrong wait key. Its result is a report, not a change to the actual operating system.

"The trace format is intentionally a classroom invention. It is **not** the Umicom Kernel syscall ABI, nor is it a capture of privileged task switches."

## 12:00–15:00 — See the real Kernel ownership boundaries

**On screen:** GitHub source tabs: `kernel/user_scheduler.c`, `kernel/message_channel.c`, `kernel/user_memory.c`, `kernel/user_ipc.c`.

**Narration:**

"The real Umicom Kernel has a greater responsibility. `user_scheduler.c` owns scheduling state and selected task frames. `message_channel.c` manages paired message endpoints with rights and handles. `user_memory.c` validates user virtual-address spans rather than accepting arbitrary pointers. And `user_ipc.c` coordinates pending calls, copied send data and completion of blocked receivers.

"One important source comment explains that a pending send retains copied bytes, while a pending receive retains an address value which must be checked again before writing. That distinction prevents a temporary pointer in a trap handler from being treated as if it stayed valid indefinitely.

"The Kernel's current execution model also has explicit single-hart assumptions. Our examples are not a substitute for testing concurrent, privileged code on the real target.

"For your final exercise, identify the owner of the queued message, the waiting task, the user destination buffer, and the saved trap frame. Follow the file links in Lesson 106, and use the Kernel's own build-and-test guide when you are ready to run QEMU. Each chapter, source example and video transcript is linked from the Bits2Banking website, so you can return to the same material at your own pace."
