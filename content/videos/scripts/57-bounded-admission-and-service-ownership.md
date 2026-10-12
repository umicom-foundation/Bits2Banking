# Episode 57 — When Too Many Requests Arrive

**Duration:** Approximately 14–18 minutes. **Source:** [Chapter 164](../../lessons/05-engineering/164-bounded-request-admission-and-backpressure.md), [Chapter 165](../../lessons/05-engineering/165-test-conditional-http-and-admission.md) and [Chapter 166](../../lessons/05-engineering/166-http-service-ownership-in-umicom.md).

## 00:00–02:10 — A busy learning website

**On screen:** Four numbered incoming requests enter a four-slot queue. A fifth is shown waiting outside the capacity boundary.

**Narration:**

“Imagine that a group of learners opens the same web lesson at almost the same moment. A service must handle incoming work, but no computer has unlimited memory or unlimited capacity. If a programme simply accepts more and more work, the memory it retains can grow beyond control. We need to decide how much work may be admitted, and what should happen when that limit is reached.

“In this episode we build a bounded admission model in C23. First we will understand the state transitions. Then we will run the programme and inspect its tests. Finally, we will compare the model with a real Umicom service boundary.”

## 02:10–04:40 — Queued is not active

**On screen:** One diagram with QUEUED and ACTIVE states, then two simulated active slots.

**Narration:**

“The moment a request enters a queue, it has not necessarily started execution. A queued request holds an admission slot. An active request is one that has been selected for work. Those two states have different cleanup rules.

“Our fixed array has four slots. The model can allow two active records. However, those numbers describe a policy model. Our demonstration is single-threaded: it does not create two threads or make sockets run in parallel. We are learning the ownership contract before implementing a real worker pool.”

**On screen:** Show the constants and `BtbAdmissionInit(&queue, 2U)` in `admission_queue.h` and `admission_demo.c`.

## 04:40–07:40 — Tickets and backpressure

**Narration:**

“Every accepted request receives a monotonically increasing ticket. That ticket belongs to one lifetime of work. Suppose we complete ticket one and reuse its array slot. A late callback still holding ticket one must not be allowed to complete the new request. The implementation therefore never reissues an old ticket.

“What if the queue is full? A fifth submission returns `BTB_ADMISSION_FULL`. That is backpressure: a visible refusal rather than an unlimited hidden queue. The caller can decide what to do next. A future concurrent server might translate capacity pressure into a protocol-level response, but this training model does not yet take over the socket listener.”

**Demonstration:**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\output\learning-build\http-loopback-server\btb-admission-demo.exe"
```

**Expected output:**

```text
Capacity: 4; maximum simulated in-flight: 2; queued: 2
Next admitted request: 3; active: 2
```

## 07:40–10:30 — Cancellation is not completion

**On screen:** One queued request is removed. A different active request receives a cancellation flag but retains its slot.

**Narration:**

“Cancelling work that has not started is relatively simple: remove the queued record. Cancelling work that is already active is different. It might already have sent bytes to the client or asked the operating system to perform a file operation. We cannot release its resources merely because someone asked it to stop.

“In the C23 model, active cancellation sets an intent flag. The active owner must still reach a completion step before its slot is freed. This is the same pattern we encountered with Umicom Kernel device requests: requesting cancellation does not prove that a device has stopped accessing memory.”

**On screen:** Show `BtbAdmissionCancel`, then `BtbAdmissionComplete`, and the stale-token check in `test_admission.c`.

## 10:30–13:20 — Test the queue, not just the happy path

**Narration:**

“Tests should exercise the capacity boundary, not simply prove that one record can be inserted. Our test suite checks full admission, FIFO selection, duplicate IDs, stale completions, cancellation before and after starting, and the model's invariants after thousands of state transitions.

“Next we run the complete existing HTTP suite. That tells us whether the original fixed routes, static-file serving and response completion still work. An educational project is most useful when its next feature does not erase the behaviour learned in the previous lesson.”

```powershell
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    --output-on-failure
```

**On screen:** Highlight the new admission tests and the earlier routing tests in the CTest output.

## 13:20–16:30 — Connect the model to Umicom

**On screen:** Compare the Bits2Banking module boundaries with the public interfaces of Umicom Framework and Umicom Kernel.

**Narration:**

“The small C23 demonstration makes admission rules visible, but Umicom Framework owns the real reusable web-server contracts. Umicom Kernel owns its own protected scheduling, IPC, file-service and driver boundaries. They are different levels of the software system.

“The development lesson is to preserve ownership. A request parser should not own a device driver. An HTTP handler should not free a socket whose lifetime belongs to the listener. A cancellation flag should not be mistaken for an acknowledgement that work has finished.

“A future lesson will add carefully bounded worker execution with genuine synchronization. Before doing that, we must establish who owns the shared route service, file handles, counters and shutdown state. Designing this clearly is a form of practical safety engineering.”

**Closing exercise:** “Write five states on paper: not admitted, queued, active, cancellation requested and completed. Decide which states hold resources. Use the C23 tests to check your explanation.”

**Final card:** Bits2Banking → Chapters 164–166 → C23 admission model → Umicom Kernel and Framework source references. **Closing:** “Pay knowledge forward: learn, contribute and help the next learner.”
