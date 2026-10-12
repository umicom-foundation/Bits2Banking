# 128. Memory-mapped I/O and transport feature negotiation

A processor uses instructions to read and write memory. Many devices also expose **registers** at addresses in a memory-mapped region. In memory-mapped I/O (MMIO), a read or write at such an address communicates with hardware rather than ordinary RAM.

This is useful for controlling devices, but dangerous if a program treats an advertised address as an ordinary pointer. This lesson explains what a driver must establish before accessing registers and how VirtIO feature negotiation constrains what that driver may do.

## 1. Separate RAM from device registers

Imagine that the Umicom Kernel is preparing to use a virtual block device. The device-tree reader reports a candidate register range. That does not mean the kernel can safely dereference the range immediately.

A complete driver admission needs several checks:

1. The region came from a checked, bounded firmware description.
2. Its bus address has been translated according to the parent bus.
3. The memory region is not being claimed by an incompatible owner.
4. The host platform supports the device's MMIO register protocol.
5. The register values identify the expected device and supported transport version.
6. The driver negotiates only capabilities for which it has an implementation.

![Device discovery, register qualification and feature negotiation are separate stages](../../assets/diagrams/device-discovery-to-driver.svg)

If any stage fails, the driver must stop without treating the resource as usable.

## 2. What do device registers contain?

An MMIO transport often exposes fields such as a device identifier, offered feature bits, queue configuration, interrupt status and a device status register.

The driver reads or writes specific register **offsets** according to the device protocol. These are not normal C structure members unless a carefully reviewed architecture adapter provides an appropriate mapping. The underlying platform can require memory barriers, cache maintenance, special address translation or different access widths.

C's `volatile` qualifier can stop the compiler from eliminating an individual access, but **`volatile` alone does not provide device ownership, cache coherence, an atomic synchronisation protocol or correct DMA ordering**.

For our course, do not experiment by dereferencing an arbitrary address in a Windows console program. The Bits2Banking laboratory is a simulation and does not map real hardware.

## 3. Understand capability bits

VirtIO devices advertise features as bits in a feature word. A modern driver checks what the device offers, determines what it understands and accepts a supported subset. The protocol also includes a status handshake so both sides agree on the accepted features before normal use.

A feature bit set to 1 means that the feature is being advertised. It does not mean a program may automatically use it without completing the negotiation process.

The following C23 example tests selected **VirtIO feature-bit numbers**. It is a pure calculation, not a register access:

```c
#include <stdbool.h>
#include <stdint.h>

#define VIRTIO_F_VERSION_1  (UINT64_C(1) << 32U)
#define VIRTIO_BLK_F_RO    (UINT64_C(1) << 5U)
#define VIRTIO_BLK_F_FLUSH (UINT64_C(1) << 9U)

static bool SupportsCourseProfile(uint64_t offered, bool wantsWrites)
{
    if ((offered & VIRTIO_F_VERSION_1) == 0U)
        return false;
    if (wantsWrites && ((offered & VIRTIO_BLK_F_RO) != 0U ||
                        (offered & VIRTIO_BLK_F_FLUSH) == 0U))
        return false;
    return true;
}
```

The code describes only a teaching-level **profile eligibility check**. It does not implement the VirtIO status handshake, queue setup, feature filtering, reset protocol or driver admission. It must not replace Umicom Kernel's transport implementation.

## 4. Read-only and writable authority

The same physical or virtual block device can support reads and writes, but a driver interface must still distinguish them.

Umicom Kernel documents separate read-only and explicitly writable admission. A writable request is accepted only after the required features and owner rules have been checked. The existence of a WRITE operation does not silently turn every open device handle into a writable handle.

In the Kernel's [writable VirtIO block guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WRITABLE_VIRTIO_BLOCK.md), writable admission also requires FLUSH support. A successful WRITE completion and a later successful FLUSH are distinct observations; actual persistence also depends on the backing storage obeying the negotiated contract.

## 5. Understand failure before continuing

Suppose your course application asks to save a Notes document:

| Observation | What can be concluded? |
| --- | --- |
| Candidate MMIO address appears in the device tree | Firmware advertised a resource. |
| Driver checks device identity and transport version | The device appears compatible with this implementation. |
| Feature negotiation completes | Driver and device have agreed on specific supported operations. |
| Queue accepts a WRITE request | Work has been made available to the device. |
| Device reports successful WRITE | The particular write has completed. |
| Device reports successful FLUSH | The negotiated persistence boundary has been reached, subject to backend behaviour. |

These statements get stronger at each step. We should not report “saved permanently” merely because the firmware described a disk or a queue accepted a request.

## 6. Use the classroom laboratories

First, run [Device Tree Inspector](../../labs/index.md) from the previous lesson and identify the candidate address and size.

Next, build the [Virtqueue Lifetime](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/virtqueue-lifetime) laboratory from Chapter 130. Notice that no real address appears in the queue API. The laboratory moves **copied bytes** between owner states and uses a fake completion to teach the protocol without accessing a real device.

To practise feature checks, predict the return values of `SupportsCourseProfile()` for these inputs:

1. Modern VirtIO (`VERSION_1`) only, read-only request.
2. Modern VirtIO plus FLUSH, writable request.
3. Modern VirtIO plus `RO` and FLUSH, writable request.
4. FLUSH only, read-only request.

The expected results are **true, true, false, false**. Explain why the `RO` bit matters only when writable admission is requested in this simplified profile.

## 7. Read the Kernel contract

Open [`include/umicom/kernel/virtio_block.h`](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/virtio_block.h). Find the difference between `UmicomKernelBlockOpen` and `UmicomKernelBlockOpenWritable`. Then inspect [`virtio_block.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtio_block.c) to see how the implementation checks its transport and retains ownership.

Do not copy device register access into Bits2Banking. The laboratory teaches how to reason about the boundary; the Kernel repository owns privileged behaviour.

**Questions to answer:** What does `volatile` not guarantee? Why is checking offered features different from completing negotiation? Can a completed WRITE by itself prove that a document will survive sudden power loss?

[Next: DMA buffer ownership](129-dma-buffer-ownership.md).
