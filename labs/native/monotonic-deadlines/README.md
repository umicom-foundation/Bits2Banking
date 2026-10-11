# Monotonic deadlines in C23

A timer needs an agreed clock. Here a **logical tick** is simply an unsigned
64-bit number controlled by the test. It is not a millisecond, a Windows
performance counter, a CPU frequency or an interrupt source.

`BtbClockAdvance` rejects time moving backwards or repeating the same tick.
`BtbDeadlineArm` checks `now + interval` before modifying the timer.
`BtbDeadlineStatus` observes state without changing it. The caller explicitly
chooses `BtbDeadlineFire` when due; cancelling at the deadline is refused.
An interval of zero means **no deadline**, not an already-expired timer.

Build on Windows UCRT64 from `C:\umicom\Umicom-Bits2Banking`:

```powershell
cmake -S ".\labs\native\monotonic-deadlines" `
  -B ".\output\learning-build\monotonic-deadlines" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\monotonic-deadlines" --parallel 2
ctest --test-dir ".\output\learning-build\monotonic-deadlines" --output-on-failure
& ".\output\learning-build\monotonic-deadlines\btb-deadline.exe"
```

Expected: one CTest passes and the demonstration prints a deadline of tick
105 followed by the expiry notification. Try changing the interval to 1, then
to `UINT64_MAX`. The latter must be rejected without overwriting the timer.

Read [Lesson 107](../../../content/lessons/05-engineering/107-monotonic-clocks-and-checked-deadlines.md)
and [Umicom Kernel timer-driven scheduling](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/TIMER_DRIVEN_USER_SCHEDULING.md).
