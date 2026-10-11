# Round-robin scheduling: runnable and waiting tasks

A scheduler chooses which **ready** task may run next. A task waiting for an
external event is not ready and must not be returned by the scheduling queue.
This hosted laboratory uses an educational fixed-capacity C23 model; it does
not start or switch operating-system processes.

## Build on Windows (PowerShell)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\round-robin-scheduler" -B ".\output\learning-build\round-robin-scheduler" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\round-robin-scheduler" --parallel 2
ctest --test-dir ".\output\learning-build\round-robin-scheduler" --output-on-failure
& ".\output\learning-build\round-robin-scheduler\btb-round-robin.exe"
```

The demonstration prints `Notes is running.` and then `Reports runs before
the newly woken Notes task.` Both CTest cases should pass.

## Walk through the source

Open `round_robin.h` to see the task handle, queue and state definitions.
`round_robin.c` owns the ready ring and generation-tagged task slots. `main.c`
demonstrates a Notes task waiting for a save completion while a Reports task
uses the processor. `test_round_robin.c` checks FIFO order, stale handles,
waiting keys, capacity and refusal without changes to results.

Increase `BTB_RR_TASK_LIMIT` and explain why the `ready` array, task slots and
handle-index check must all describe the same capacity. Rebuild and rerun.

[Umicom Kernel's scheduler](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_scheduler.c)
and [blocking IPC](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_ipc.c)
are the authoritative privileged implementations. They have different lifetime,
trap-frame, privilege and device contracts. No real timer interrupt, context
switch, syscall, SMP lock or protected user address is present in this lesson.
