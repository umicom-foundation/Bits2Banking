# Build a bounded copied-message channel in C23

This small, single-threaded programme models one aspect of inter-process communication: a sender passes bytes to a queue, and the queue takes ownership of its **own copy**. The real Umicom Kernel channels implement considerably more, including handles, rights, endpoint lifetimes and syscall checks.

## Windows — PowerShell

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\bounded-channel" -B ".\output\learning-build\bounded-channel" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\bounded-channel" --parallel 2
ctest --test-dir ".\output\learning-build\bounded-channel" --output-on-failure
& ".\output\learning-build\bounded-channel\btb-bounded-channel.exe"
```

Expected demonstration: `Receiver 22 accepted message 1 from 10: Notes: save the weekly report`. Two CTest cases check successful delivery, FIFO order, buffer ownership and refusal when the queue or output buffer is too small.

## Read the source

Begin with `channel.h`. `BtbChannel` is a fixed array of four messages. `BtbChannelSend` copies the caller's bytes into one slot and advances the queue only after checking capacity. `BtbChannelReceive` refuses an unauthorised recipient or an inadequate destination **without consuming the message**. After successful delivery, it zeroes the vacated slot.

Change `BTB_CHANNEL_DEPTH` from 4 to 2, rebuild and rerun the tests. Observe that the current test explicitly expects four available slots: the test must be updated deliberately rather than silently ignored.

The lab does not perform real IPC, validate user virtual addresses, create kernel handles, protect against concurrent access, or transmit data over a network. For real design, examine [Umicom Kernel message channels](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_channel.c) and [the message service](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_service.c).
