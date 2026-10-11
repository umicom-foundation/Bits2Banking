# Timed service waits — C23 composition

The Notes task is blocked while it waits for an event, but it must not wait
forever when a finite timeout has been requested. This laboratory composes:

- The existing [`round-robin-scheduler`](../round-robin-scheduler/) task API.
- The new [`monotonic-deadlines`](../monotonic-deadlines/) logical clock.
- A small `service.c` that only coordinates those owners.

The service owns its timer but borrows the scheduler and clock. A signal with
an incorrect event key cannot wake the task. A signal at or beyond the
established deadline loses to the timeout. The wake changes the task to **Ready**;
the scheduler determines when it next becomes **Running**. Cancelling a pending
wait stops the task; it does not pretend to unwind code or free a real process.

From `C:\umicom\Umicom-Bits2Banking` with UCRT64 GCC and Ninja available:

```powershell
cmake -S ".\labs\native\timed-service-waits" `
  -B ".\output\learning-build\timed-service-waits" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\timed-service-waits" --parallel 2
ctest --test-dir ".\output\learning-build\timed-service-waits" --output-on-failure
& ".\output\learning-build\timed-service-waits\btb-timed-service.exe"
```

Expected: three passing CTest cases. The executable demonstrates a timeout at
tick 105 and a separate scheduler dispatch. Tests also cover early event
signals, exact-deadline ties, invalid keys, cancellation, overflow and the
absence of an executable task after cancellation.

**Important boundary:** This single-threaded demonstration does not program a
physical timer, install an interrupt, implement an actual blocking syscall or
synchronise across CPU cores. The real Umicom Kernel owns all those concerns.

Read [Lesson 109](../../../content/lessons/05-engineering/109-compose-a-timed-service-wait.md).
