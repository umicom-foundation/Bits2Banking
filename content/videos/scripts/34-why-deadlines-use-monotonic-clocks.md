# Episode 34 — Why deadlines use monotonic clocks

**Duration:** 11–14 minutes  
**Reading:** [Lesson 107](../../lessons/05-engineering/107-monotonic-clocks-and-checked-deadlines.md)  
**Source:** [`labs/native/monotonic-deadlines`](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/monotonic-deadlines)

## 00:00–01:20 — What happens when a service is slow?

**On screen:** The Umicom Notes application with a pending search request; a progress indicator and a Cancel button, but no fake working backend.

**Narration:** “A Notes application often asks another component to perform work. It may request a search index, save a document or wait for a reply. Sometimes that work takes longer than expected. A well-designed application should not keep asking the same question in a tight loop or pretend the work completed successfully. It needs to understand how long it is willing to wait and what happens when that limit is reached. Today we will build the small part that decides whether a deadline has expired.”

## 01:20–03:30 — Two different clocks

**On screen:** A wall clock showing 15:00; the time is corrected backwards to 14:59. Beside it a logical tick counter moves only upwards.

**Narration:** “The date and time shown by the operating system is a wall clock. That makes it useful for labelling a report with a date, but the reading can be corrected. If we use that reading alone for a timeout, a clock adjustment can accidentally make the timeout shorter or longer. A monotonic clock has a different purpose: it tracks progress that does not go backwards. Real operating systems specify which clock is used and its units. For today's lesson, we simplify the clock further. Our test controls a logical tick counter. When it says 100, then 104, then 105, it means only that those observations happened in increasing order. We do not pretend they represent milliseconds or a physical CPU timer.”

**On screen:** Display the [monotonic deadline diagram](../../assets/diagrams/monotonic-deadline-timeline.svg).

## 03:30–06:15 — Checked addition in C23

**On screen:** `deadline.c` with `BtbDeadlineArm` and the check `clock->now > UINT64_MAX - interval` highlighted.

**Narration:** “Our starting tick is 100 and our timeout interval is 5. We add them to reach deadline 105. This sounds trivial until the counter approaches the largest unsigned 64-bit number. In C, unsigned integer arithmetic wraps when a result is too large. Adding without checking could turn a future deadline into a very small number. That might cause a service to report an immediate timeout or leave its state inconsistent. Instead, we compare the starting value with the maximum minus the interval. Only when the addition fits do we calculate the deadline and publish the new timer state. Notice that validation comes before changing the caller's timer. This is a general pattern throughout Umicom Framework: a refused update should not quietly damage the old state.”

**Demonstration:** Show `BtbDeadlineArm()` returning `BTB_TIMER_OVERFLOW` when the clock is `UINT64_MAX` and the interval is 1.

## 06:15–09:15 — Build, test, observe

**On screen:** PowerShell and `C:\umicom\Umicom-Bits2Banking`.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\monotonic-deadlines" `
    -B ".\output\learning-build\monotonic-deadlines" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\output\learning-build\monotonic-deadlines" --parallel 2
ctest --test-dir ".\output\learning-build\monotonic-deadlines" --output-on-failure
& ".\output\learning-build\monotonic-deadlines\btb-deadline.exe"
```

**Narration:** “CMake describes the programme and its test. Ninja builds the C23 source with our compiler. CTest runs the assertions. The demonstration prints a deadline of 105 and then reports that the timer expired at that tick. Notice that we did not call a sleep function. We advanced the logical clock ourselves so the experiment is repeatable. The test also moves the clock to 104 and confirms that it is not yet due. At 105 it becomes due. A cancellation at the exact deadline is refused by this exercise because timeout takes precedence.”

## 09:15–11:30 — What does the timer not do?

**On screen:** Show two boxes: Deadline decision and Scheduler dispatch, with a gap between them.

**Narration:** “A timer is not a scheduler. It tells us when a waiting condition has reached its limit; it does not itself run another task. In the next chapter we will make the Notes task Ready after a timeout and let the scheduler choose when it runs. In a real Kernel, hardware interrupts, Assembly trap entry and saved execution state introduce additional responsibilities. Those belong in Umicom Kernel, not in this teaching clock. One useful exercise is to change the timeout from five ticks to three and update the expected deadline. Then intentionally try an overflowing timeout and confirm that the previous state remains unchanged.”

**End screen:** Links to [Lesson 107](../../lessons/05-engineering/107-monotonic-clocks-and-checked-deadlines.md), [Lesson 109](../../lessons/05-engineering/109-compose-a-timed-service-wait.md) and the [Umicom Kernel timer-driven scheduling guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/TIMER_DRIVEN_USER_SCHEDULING.md).
