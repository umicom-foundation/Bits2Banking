# Blocking IPC and service lifetimes in C23

When a Notes service asks for a message and the queue is empty, it must wait
without repeatedly running. The scheduler removes the task from the ready
queue. After a sender copies a message, the queue becomes ready; a separate
poll registers the wake, and the scheduler eventually dispatches the receiver.

This laboratory **reuses** the exact `channel.c` and `round_robin.c` from the
earlier lessons. `session.c` is a small coordination adapter, not another
message queue or scheduler.

## Build using PowerShell

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\blocking-ipc-lifetimes" -B ".\output\learning-build\blocking-ipc-lifetimes" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\blocking-ipc-lifetimes" --parallel 2
ctest --test-dir ".\output\learning-build\blocking-ipc-lifetimes" --output-on-failure
& ".\output\learning-build\blocking-ipc-lifetimes\btb-blocking-ipc.exe"
```

The demonstration states that Notes is waiting and then reports copied bytes
after wake-up. Two tests cover accepted-message delivery, unchanged results
on insufficient buffer capacity, cancellation, stale task handles and retained
queue contents after a consumer closes.

## Trace the ownership boundary

The scheduler owns task state; the channel owns copied message bytes; the
service holds **borrowed** pointers to both. Close cancels a pending receiver
but does not destroy somebody else's channel. A later approved consumer may
still inspect a message which was already accepted before cancellation.

The model is single-threaded. `WaitForMessage` checks queue emptiness and
registers the waiter without allowing another task to run between those steps.
This cannot be substituted for a real multi-core atomic wait protocol: actual
Umicom Kernel uses its own user IPC scheduler, checked user addresses, trap
frames, cancellation and privileged ownership rules.

Compare the code with [Kernel user IPC](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_ipc.c), [message service](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_service.c), and [message channels](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_channel.c).
