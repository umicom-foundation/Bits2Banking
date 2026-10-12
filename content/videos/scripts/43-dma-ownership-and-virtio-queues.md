# Episode 43 — DMA ownership, VirtIO queues and safe completion

**Duration:** approximately 13–16 minutes  
**Related chapters:** [129. DMA buffer ownership](../../lessons/05-engineering/129-dma-buffer-ownership.md), [130. VirtIO split queues](../../lessons/05-engineering/130-understand-virtio-split-queues.md) and [131. Umicom Kernel source](../../lessons/06-umicom/131-read-umicom-kernel-device-discovery.md)

## 00:00–02:00 — After the user presses Save

**On screen:** A Notes document with an unsaved change, then a separate storage queue.

**Narration:**

“We have followed a storage device from a firmware description to a possible driver. Now imagine a note-taking program saving a document. The service has a buffer containing its new text. The driver has to hand data to the device, but it must do so without exposing an editor's changing memory as if it belonged permanently to the hardware.

“A common mechanism is DMA, which means Direct Memory Access. A device can transfer bytes from or to a suitably prepared region of memory without asking the processor to copy each byte through a register.

“That sounds convenient. It also means we have two participants who might access the same memory at different times. Good driver code needs a very clear answer to this question: when is it safe to release the buffer?”

## 02:00–04:30 — A buffer has more than one lifetime

**On screen:** [DMA buffer lifetime](../../assets/diagrams/dma-buffer-lifetime.svg).

**Narration:**

“Start with the original Notes document. The editor owns its working copy. A storage service can copy accepted bytes into a driver-owned buffer, often called a bounce buffer. The driver then arranges for the device to access that buffer.

“The driver has not given up the responsibility for memory allocation. It has granted the device the ability to use the memory for a particular operation. If the driver frees that memory too early, an old device request might read or overwrite memory now being used by an entirely unrelated object.

“Look at the diagram. There are four moments: copying the input, preparing the buffer, publishing work to the device and observing completion. Cancellation may be requested during the third stage, but it does not itself complete the fourth.

“Even a timeout is just the end of a wait. It does not mean that the device has stopped working. This distinction is important in operating-system drivers, file services, network communication and transaction processing.”

## 04:30–06:30 — What is a VirtIO split queue?

**On screen:** [VirtIO split queue](../../assets/diagrams/virtio-ring-ownership.svg).

**Narration:**

“VirtIO provides a standard way for a guest operating system to communicate with virtual hardware. A split virtqueue has three main components. The descriptor table describes buffers. The available ring tells the device which descriptor chains are ready. The used ring tells the driver which chains the device has finished using.

“Publication and completion are deliberately separate. The driver writes a new available entry and makes it visible according to the protocol. Later, the device writes a used entry. The driver must check the returned identifier, status and byte counts before it can report a successful result.

“The real VirtIO specification governs descriptor flags, memory layout, indexes and barriers. We are about to run a classroom model using simple arrays. Its purpose is to explain lifetime rules, not to produce a driver compatible with real MMIO hardware.”

## 06:30–09:45 — Run the C23 laboratory

**On screen:** PowerShell then `queue.h` and `queue.c`.

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

**Narration:**

“First, CMake configures the project. Ninja builds a small reusable C23 library and two programs. CTest checks copied buffers, FIFO ordering, cancellation, reset and stale tokens.

“Open `BtbVqPrepare`. It validates the input and copies every accepted byte into a queue-owned slot. Try modifying the caller's original input after preparation. The queue's copy remains unchanged.

“Next, open `BtbVqPublish`. The operation checks the owner and the current state. It publishes a token to the available ring, but it does not claim that the device has processed it.

“Now find `BtbVqCancelRequested`. That function only records that cancellation has been requested. It does not release the slot. Our demonstration then calls `BtbVqSimulateComplete` and collects a successful result. You should see that the cancellation was requested even though a completion was subsequently observed.

“The exact lesson is that an instruction to cancel and a report of completion are not contradictory. They may race. A reliable program needs to observe the final result rather than assume that one of them must have happened first.”

## 09:45–11:30 — Reuse without stale handles

**On screen:** Diagram of slot 0 used twice, with generation 1 and then generation 2.

**Narration:**

“A bounded queue eventually reuses its slots. If a request uses slot number zero, and later another request uses the same slot, how does the driver distinguish the old request from the new one?

“Our laboratory attaches a generation value to the slot number. The complete token contains both fields. When the request is collected and its memory cleared, the generation advances. An old token is then rejected. This prevents a stale request identifier from silently naming an unrelated later request.

“Generation values are not passwords. They help detect mistakes and stale ownership. Actual authority also requires checking the owner and current state.”

## 11:30–13:30 — Why reset must be acknowledged

**On screen:** State diagram for `REQUEST_RESET`, retained buffers, `SIMULATE_RESET_ACK` and cleanup.

**Narration:**

“Suppose a device fails to complete. A driver may request a reset. Can it release its buffers immediately? Not safely. Requesting reset is not the same thing as knowing the device has stopped using its queue.

“Our model freezes new work when reset is pending. Existing published buffers remain retained. A separate test operation simulates observing a reset acknowledgement, and only then does the model clear the buffers and allow reuse.

“This is only a classroom simulation. In the real Umicom Kernel, actual device and platform code must establish the reset condition. A unit test that calls `SimulateResetAcknowledged` cannot prove that hardware is quiescent.”

## 13:30–15:30 — Connect it to Umicom Kernel

**On screen:** [`virtio_block.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtio_block.c) and its public header.

**Narration:**

“The Umicom Kernel implementation owns the real transport. It qualifies compatible devices, prepares queue and bounce pages, observes completions, and preserves resources while the device might still access them.

“It also distinguishes ordinary reads from explicitly authorised writes. For writes, a validated completion and a later successful FLUSH are different events. A successful write does not automatically prove durable storage after power loss.

“Your next exercise is to read the public `UmicomKernelBlockMutationOutcome` values: `NOT_SUBMITTED`, `SUBMITTED_UNCONFIRMED` and `COMPLETED`. Write a sentence explaining what each one proves, and then find the code that preserves memory when a request has an uncertain result.

“You can follow these steps on the Bits2Banking website and compare the classroom code with the authoritative Kernel repository. Keep the two implementations separate: one teaches the concept; the other controls an actual target platform.”

**References:** [Chapters 129–131](../../lessons/05-engineering/129-dma-buffer-ownership.md), [Virtqueue laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/virtqueue-lifetime), [Kernel driver](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtio_block.c), [Kernel writable-block guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WRITABLE_VIRTIO_BLOCK.md).
