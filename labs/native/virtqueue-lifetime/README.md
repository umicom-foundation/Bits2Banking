# Understand device-buffer ownership with a C23 queue

This is a **hosted teaching model**, not a VirtIO transport. It uses arrays instead of DMA, and functions called by the tests stand in for a device. It never uses MMIO or opens a real block device.

## Build on Windows (PowerShell)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\virtqueue-lifetime" `
    -B ".\output\learning-build\virtqueue-lifetime" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\virtqueue-lifetime" --parallel 2
ctest --test-dir ".\output\learning-build\virtqueue-lifetime" --output-on-failure
& ".\output\learning-build\virtqueue-lifetime\btb-vq-demo.exe"
```

The two tests check copied request bytes, ownership checks, FIFO ordering, cancellation, strict reset-before-reuse and stale-token rejection. The demo shows a cancelled request completing before cancellation has taken effect.

## Follow the buffer lifetime

1. `BtbVqPrepare` copies caller-owned bytes into one queue slot.
2. `BtbVqPublish` makes the slot available to the simulated device.
3. `BtbVqCancelRequested` records intent, but leaves the published bytes untouched.
4. `BtbVqSimulateComplete` reports a terminal result and moves the token into the used ring.
5. `BtbVqCollect` copies the result, clears the old slot and changes its generation.
6. `BtbVqRequestReset` instead freezes admission and retains outstanding slots.
7. `BtbVqSimulateResetAcknowledged` models a separately observed reset acknowledgement; **only then** may slots be reused.

A real DMA engine can continue accessing memory after a software timeout. No classroom function can provide hardware reset evidence. See [the VirtIO lesson](../../../content/lessons/05-engineering/130-understand-virtio-split-queues.md) and [Umicom Kernel's block-driver contracts](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WRITABLE_VIRTIO_BLOCK.md).
