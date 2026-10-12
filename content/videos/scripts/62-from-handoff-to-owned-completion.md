# Episode 62 — From Handoff to an Owned Completion

**Bits to Banking · Umicom Foundation · Presenter script**  
**Companion lessons:** [177](../../lessons/05-engineering/177-from-work-handoff-to-completion-delivery.md), [178](../../lessons/05-engineering/178-compose-existing-c23-libraries.md).  
**Run time:** approximately 9 minutes · **Technical language:** C23.

## Learning result

The viewer can explain the three separate moments of request acceptance, execution completion and result delivery, and identify the source line responsible for releasing a work slot. No network or external bank service is required.

### 00:00–01:15 — The real-world question

**Visual:** An Umicom Bank cash-position tab submits `CASH|GBP|ACCOUNT-A`. Three tick boxes appear: Accepted, Processed, Delivered.

**Narration:** “An application can accept a request before performing any work. It can finish work before the original requester has received the answer. If these stages are treated as the same event, results can be lost or applied to the wrong screen. Today we will connect two existing C23 teaching components so the distinction becomes visible.”

**Teaching pause:** Ask the viewer whether ‘HTTP 200 generated’ necessarily means the browser read the complete response. No: disconnection or buffering may intervene.

### 01:15–02:45 — Open the two earlier libraries

**Screen:** `labs/native/work-handoff/handoff.h` and `labs/native/completion-queue/queue.h` side by side. Highlight the eight work slots, four completion slots, and generation-bearing token.

**Narration:** “We are not writing another queue. One existing component owns copied request bytes. Another owns short terminal notifications. Their data types were built for separate lessons; the adapter explains their relationship rather than modifying either contract.”

**Visual:** `dispatch-composition.svg`. Pause over each boundary and label *owned*, *borrowed* or *copied*.

### 02:45–04:45 — Follow a request through C23

**Screen:** In `dispatch.c`, locate `BtbDispatchSubmit`, `BtbDispatchStep`, and `BtbDispatchReceive` in that order.

**Narration:** “Submit validates and copies the request. Step borrows its bytes for a synchronous diagnostic operation, marks the work terminal and publishes a completion notice. Receive copies the receipt to its caller, removes the notice and releases the work slot. Because the receipt is a value, it remains valid after the internal slot is reused.”

**Engineering note on screen:** FNV-1a is a deterministic diagnostic digest, **not** a cryptographic hash and not an accounting proof.

### 04:45–06:20 — Compile and run

**Screen / terminal, executed as interactive commands:**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\work-dispatch" -B ".\output\learning-build\work-dispatch" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-dispatch" --parallel 2
& ".\output\learning-build\work-dispatch\btb-work-dispatch-demo.exe"
```

**Expected screen:** Three accepted request IDs, three terminal receipts, final `PASS`.

**Narration:** “These are deterministic classroom records. No banking credentials, socket endpoints, files or users have been created by the demonstration.”

### 06:20–07:45 — Inspect invariants

**Screen:** Highlight `BtbDispatchInvariants` and the counters `accepted`, `succeeded`, `cancelled`, `delivered`.

**Narration:** “The dispatcher knows how many requests still own storage and how many terminal notices are waiting. The numbers must reconcile. This is not merely a performance statistic; it is a way of checking that transitions have not lost responsibility for work.”

### 07:45–09:00 — Summary and learner task

**Narration:** “Draw this flow yourself. Put a star on the operation that frees a slot. Explain why the completion queue is smaller than the work queue. Then run the nine CTest cases and record the compiler version and the results.”

**On-screen exercise:** Change the mock request to a different report name, rebuild and compare the digest. State why equal digests would not establish a cryptographic guarantee.

**Production boundary:** The lab is single-owner and synchronous. Framework production capability requires an independent review; the sample is not a worker pool.
