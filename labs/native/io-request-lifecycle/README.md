# Device I/O request lifetimes in C23

This exercise composes the `../completion-queue` library. It models requests and terminal notifications. No disk, network adapter, hardware register or Kernel device is accessed.

## Build on Windows (PowerShell)

From `C:\umicom\Umicom-Bits2Banking`:

```powershell
cmake -S .\labs\native\io-request-lifecycle -B .\output\learning-build\io-request-lifecycle -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build .\output\learning-build\io-request-lifecycle --parallel 2
ctest --test-dir .\output\learning-build\io-request-lifecycle --output-on-failure
```

Both tests should pass. The demonstration prints `I/O request 1 completed: 256 of 256 bytes.`

## Inspect each transition

1. `BtbDeviceSubmit` accepts a 256-byte request and returns its new ID.
2. `BtbDeviceRequestCancel` records a request to stop. **No completion exists yet.**
3. `BtbDeviceComplete` accepts a terminal result into the shared completion queue. A full queue refuses the transition and leaves the request pending.
4. `BtbDeviceCollect` removes the oldest completion. Only then does the service release the request slot.
5. `BtbDeviceQuiesce` refuses new submissions but allows outstanding work to finish.
6. `BtbDeviceRelease` refuses to destroy the service while any request remains outstanding.

Read `test_device.c` to see cancellation losing a race to successful completion and a full queue blocking a terminal transition without losing a request.

## Next experiment

Change the capacity of the completion queue in its single authoritative header. Rebuild both projects. Explain why an accepted request still needs to be retained when the queue cannot hold another completion.
