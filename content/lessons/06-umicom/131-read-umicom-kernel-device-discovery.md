# 131. Follow device discovery and VirtIO ownership in Umicom Kernel

The previous four chapters introduced device trees, MMIO, DMA and virtqueues using safe C23 examples. We can now follow those ideas through the **real Umicom Kernel source** without editing or replacing the Kernel's implementation.

Umicom Kernel is an independent native-kernel research project using C23 and RISC-V Assembly. It is not the same thing as Umicom Framework, and its development target must not be confused with the complete Umicom OS distribution.

## 1. Find the authoritative implementation

Start at the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel). Open these sources in the following order:

| Source | What you will learn |
| --- | --- |
| [`kernel/device_tree.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/device_tree.c) | Initial firmware device-tree extent validation and physical-memory reservation concerns |
| [`kernel/hardware_catalogue.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/hardware_catalogue.c) | Copied hardware observations and bus-address translation |
| [`include/umicom/kernel/virtio_block.h`](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/virtio_block.h) | Public VirtIO block contracts and ownership states |
| [`include/umicom/kernel/virtio_block_protocol.h`](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/virtio_block_protocol.h) | Protocol constants and transport layout definitions |
| [`kernel/virtio_block.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtio_block.c) | Checked device admission, queues, request lifetimes and reset cleanup |
| [`kernel/virtio_block_validation.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtio_block_validation.c) | Hardware-facing and synthetic validation paths |

The background documents are [Hardware Discovery](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/HARDWARE_DISCOVERY.md) and [Writable VirtIO Block](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WRITABLE_VIRTIO_BLOCK.md).

## 2. Identify the device-tree trust boundary

Read `kernel/device_tree.c`. The first responsibility is not starting a storage driver. It is establishing which bytes of the firmware-supplied device tree can be examined and which pages must not be handed to the ordinary physical-page allocator.

Then follow `kernel/hardware_catalogue.c`. An FDT `reg` property describes an address in the space defined by its parent bus. That address is not necessarily a physical CPU address. Supported `ranges` properties translate addresses through the bus hierarchy.

Compare this with the `BtbFdtInspect` laboratory from [Chapter 127](../05-engineering/127-inspect-device-tree-in-c23.md). Our classroom tool supports one small two-cell `reg` form. The Kernel's hardware catalogue has a much broader, separately governed contract. We must not substitute the classroom parser for it.

## 3. Check a driver's admission sequence

Open `include/umicom/kernel/virtio_block.h` and locate `UmicomKernelBlockOpen` and `UmicomKernelBlockOpenWritable`.

Explain why they are separate. A read-only handle is not automatically authorised to write simply because the backend happens to support writes. A writable request requires additional admission and negotiated feature support.

Find `UmicomKernelBlockOperations`. Its callbacks describe where platform-specific register access, barriers and time observations belong. The driver is not permitted to interpret the device-tree byte array itself as a memory-mapped register pointer.

In `virtio_block.c`, look for the operations associated with feature negotiation, queue ownership, request handling and reset. Follow the status checks rather than skipping directly to a successful return path.

## 4. Look for retained memory ownership

The driver keeps owned queue and data frames instead of borrowing arbitrary application memory for DMA.

Its source explains an important rule: **a timeout is not proof that the device has relinquished its access to memory**. If reset completion cannot be established, the driver retains enough ownership to retry cleanup later.

Compare this with the hosted [Virtqueue Lifetime laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/virtqueue-lifetime). The test calls a fake reset-acknowledgement function. The actual Kernel must obtain its own evidence from the device before releasing DMA-accessible frames.

A malicious DMA-capable device is outside the guarantees of the Kernel's no-IOMMU teaching profile; the documentation explicitly states that assumption.

## 5. Understand the three write outcomes

The Kernel defines `UmicomKernelBlockMutationOutcome`:

```c
UMICOM_BLOCK_NOT_SUBMITTED
UMICOM_BLOCK_SUBMITTED_UNCONFIRMED
UMICOM_BLOCK_COMPLETED
```

Read the comments adjacent to the enumeration in the [public header](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/virtio_block.h).

- **Not submitted** means the attempted mutation was not made available to the device.
- **Submitted but unconfirmed** means the device may already have changed some or all bytes, but the driver cannot confirm complete success.
- **Completed** means a validated successful result was observed for that request. For a WRITE, this alone is not a claim of durable storage; the documented FLUSH boundary is separate.

Imagine an accounting service writing a fictional entry. Reporting “saved” when the device might have accepted only a partial write is misleading. A higher-level system needs its own transaction, recovery and durability rules, not just one block-completion status.

## 6. Build the actual Kernel independently

After installing the compiler, linker and QEMU dependencies described in the [Kernel's Windows setup guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WINDOWS_BEGINNER_SETUP.md), use PowerShell in the **separate Kernel repository**:

```powershell
Set-Location "C:\umicom\umicom-kernel"

cmake --preset riscv64-clang-debug
cmake --build --preset riscv64-clang-debug --parallel 2
ctest --preset riscv64-clang-debug --output-on-failure
```

This chapter only gives commands to readers who choose to build the Kernel; **Bits2Banking Update 20 does not change that repository**. Always follow the Kernel's current `BUILD_AND_TEST.md` for target-specific configuration and QEMU acceptance.

Passing a classroom host test does not qualify a physical device. Likewise, a successful QEMU test proves the stated guest configuration, not every possible storage controller.

## 7. Prepare a useful contribution

Choose one ownership question and investigate it end to end:

1. Select a public driver operation, such as `UmicomKernelBlockRead`.
2. Find the conditions checked before it accepts a request.
3. Trace what remains owned after a successful completion.
4. Trace what remains owned after a timeout or reset failure.
5. Identify the focused Kernel test that demonstrates that distinction.
6. Write a short explanation referring to specific source lines and current test behaviour.

You now have the foundation for a meaningful documentation improvement or a new test proposal. The Kernel implementation stays authoritative; our classroom examples continue to be small, readable and independently buildable.

## Review questions

**Why is a copied hardware catalogue safer than keeping unchecked pointers into a temporary FDT buffer?** Why does a discovered `reg` address still require bus translation and driver admission? What is the difference between a successful WRITE completion and confirmed persistence? When would the driver retain frames after a failure rather than release them immediately?

Return to [Chapter 127](../05-engineering/127-inspect-device-tree-in-c23.md) if you want to practise interpreting FDT bytes, or continue with [Chapter 130](../05-engineering/130-understand-virtio-split-queues.md) to revisit the queue ownership model.

## Continue with a connected course

[Read firmware bytes without following their addresses](../../courses/umicom-kernel-from-scratch/lessons/05-firmware-metadata.html) — Follow the shared device-tree reader before interpreting device bindings.

[Find prerequisites and other learning routes](../../start/systems-learning.md). Return to this chapter whenever the course refers to its concepts.
