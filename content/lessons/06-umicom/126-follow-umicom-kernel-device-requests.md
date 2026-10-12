# 126. Follow device request ownership in Umicom Kernel

Umicom Kernel is being developed as a native C23 and RISC-V Assembly operating-system kernel. Its driver code is the authoritative implementation. The Bits2Banking exercises prepare you to read that code, but the exercises are not substituted for the actual Kernel.

## Find the real source

Open these files from the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel):

- [`include/umicom/kernel/virtio_block.h`](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/virtio_block.h) declares the public driver contracts and status values.
- [`kernel/virtio_block.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtio_block.c) implements device admission, transport operations, request handling and cleanup.
- [`kernel/physical_memory.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/physical_memory.c) manages physical page-frame ownership.
- [`docs/WRITABLE_VIRTIO_BLOCK.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WRITABLE_VIRTIO_BLOCK.md) explains explicit writable authority, accepted writes and flush semantics.
- [`docs/INTERRUPT_OWNERSHIP.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/INTERRUPT_OWNERSHIP.md) explains interrupt masking and source ownership.

## Step 1 — Admission is not authority for every operation

The block interface has separate admission paths for read-only access and explicit writable access. `UmicomKernelBlockOpen` does not automatically gain permission to issue writes merely because a device is physically capable of them. Writable access requires `UmicomKernelBlockOpenWritable` and feature negotiation, including FLUSH support.

This separation resembles permissions on a Notes document. Knowing its location is not the same as having permission to change it.

## Step 2 — A request may outlive its caller's wait

The Kernel's VirtIO block driver uses a bounded split queue, a request header, a status field and an owned bounce page. The caller's buffer is not directly exposed to DMA. The driver must retain its queue and bounce memory while the hardware could still use those addresses.

If a wait times out, the host may not yet know whether the device stopped. The driver therefore retains resources and performs an explicit reset and acknowledgement sequence before releasing device-accessible frames.

Compare this to the [cancellation lesson](../05-engineering/124-cancel-quiesce-and-release-device-work.md): a caller's cancellation request and the device's terminal status are different observations.

## Step 3 — Write completion is not a durability guarantee

The Kernel documentation distinguishes three points:

1. A write request has been published, so the device is permitted to act.
2. A complete, validated write result reports success for that operation.
3. A later successful FLUSH reports the negotiated stable-write boundary for preceding completed writes, provided the backend honours it.

A successful write alone is not a promise that its data survives power loss. The underlying device, cache policy and storage backend determine whether the durability condition is actually satisfied.

For a Treasury Management System this distinction matters: a response that an accounting record was accepted is not necessarily proof that every durable ledger copy has committed. A real application also needs its own transaction and persistence controls.

## Step 4 — Compare boundaries, not source size

| Classroom project | Actual Kernel concern |
| --- | --- |
| Fixed completion queue | VirtIO descriptor and used-ring bookkeeping |
| Request ID | Generation-tagged driver handle and private request ownership |
| Cancel request | Timeout, reset and retained resource obligations |
| Quiesce and collect | Device stop, completion validation and safe DMA-frame release |
| Test fixture | QEMU target qualification and real protocol observations |

Do not copy the classroom queue into `kernel/virtio_block.c`. The Kernel already owns its transport and memory-lifetime policies. A valid contribution would first identify a missing behaviour, write a focused acceptance test, then extend that single authoritative implementation.

## Build the real Kernel

After completing the toolchain setup described in the [Kernel build and test guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md), use PowerShell:

```powershell
Set-Location "C:\umicom\umicom-kernel"
cmake --preset riscv64-clang-debug
cmake --build --preset riscv64-clang-debug --parallel 2
ctest --preset riscv64-clang-debug --output-on-failure
```

QEMU RISC-V tests are different from ordinary host CTest laboratories. A successful host simulator test is not evidence that a physical device or native Kernel build has passed qualification.

## Next experiment

Read the public `UmicomKernelBlockMutationOutcome` enumeration. Explain, in your own words, the difference between `NOT_SUBMITTED`, `SUBMITTED_UNCONFIRMED` and `COMPLETED`. Which outcomes are possible if a timer expires after the request was published? Why must the driver retain enough ownership to retry cleanup?
