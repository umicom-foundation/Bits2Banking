# Episode 63 — When the Completion Queue Is Full

**Bits to Banking · Umicom Foundation · Presenter script**  
**Companion lessons:** [179](../../lessons/05-engineering/179-downstream-capacity-and-fair-scheduling.md), [180](../../lessons/05-engineering/180-cancellation-identity-and-graceful-drain.md), [181](../../lessons/05-engineering/181-verify-and-integrate-umicom-services.md).  
**Run time:** approximately 10 minutes · **Technical language:** C23.

### 00:00–01:30 — Two different capacities

**Visual:** `dispatch-two-queues.svg` shows eight work slots and four completion slots.

**Narration:** “We can accept eight short requests, but we can only retain four undelivered results. If the receiver is slower than the processor, the processor must stop before producing a fifth terminal notification. The safe response is backpressure, not an unbounded array or a silent dropped result.”

**On-screen definition:** Backpressure = deliberately refusing or delaying work when the next stage has no capacity.

### 01:30–03:40 — Read a real guard

**Screen:** `BtbDispatchStep` in `dispatch.c`.

**Narration:** “The capacity check occurs before we acquire a new work item. This ordering is significant. If we acquired work first and had nowhere to record its completion, we would create an additional lifecycle problem. We are using the previously tested completion FIFO rather than adding an application-local copy.”

**Demo:** Run `ctest --test-dir ".\output\learning-build\work-dispatch" -R "dispatch.capacity" --output-on-failure`. Then open `TestCapacity` and narrate each state transition.

### 03:40–05:15 — Why cancellation also needs space

**Visual:** A red “Cancel” command is sent while the results queue is full.

**Narration:** “Cancellation is a terminal outcome. If we erase a queued request without recording its cancellation, the original requester may wait forever. In this teaching contract, cancelling a queued request requires one completion slot. If the queue is full, the cancellation request is refused without changing the work state.”

**Teaching question:** Does cancellation automatically undo an already completed payment or trade? **No.** That is a domain-specific reversal governed by the authoritative service, not an effect of stopping a UI request.

### 05:15–07:05 — Stale identity protection

**Screen:** `TestStale`; show `slot`, `generation`, and `requestId` for old and new records.

**Narration:** “A slot is physical storage. A generation is its lifetime. The old request cannot cancel a later request that happens to occupy the same slot. We test all identity fields rather than trusting a slot index alone.”

**Expected observation:** The old cancellation returns `BTB_DISPATCH_STALE` after slot reuse; the newer request can still be cancelled normally.

### 07:05–08:45 — Graceful shutdown

**Visual:** `dispatch-shutdown.svg`.

**Narration:** “Quiesce closes admission. It does not erase queued work. Later, all accepted work is resolved and all terminal results are delivered. The original handoff queue can be execution-drained while a result remains outstanding. The composed dispatcher therefore has a stronger drained predicate.”

**Demo:** Run the `dispatch.quiesce` test. Pause between `Step` and `Receive` and display both drained predicates.

### 08:45–10:00 — Review and exercise

**Narration:** “Run the full suite in GCC or Clang. Record which compiler you used. We validated a serial state machine; we have not implemented worker threads, an event loop, a live banking transaction or a production Umicom Framework integration.”

**Learner assignment:** Predict the counters after four successes and one cancellation notice, then consume three results and inspect the remaining owned records. Explain why the identities remain valid until receipt.
