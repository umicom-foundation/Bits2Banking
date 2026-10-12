# Episode 40 — From a saved note to a completed device request

**Length:** approximately 10–13 minutes  
**Companion reading:** [Lesson 122](../../lessons/05-engineering/122-device-io-from-submit-to-completion.md), [Lesson 123](../../lessons/05-engineering/123-build-a-bounded-completion-queue.md)  
**Source:** [Bits2Banking C23 I/O laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/io-request-lifecycle)

## Opening — 0:00–1:15

**On screen:** A simple Notes application with a Save button. A small status reads “Saving…” before changing to “Saved”.

**Narration:**

“When we click Save, we expect the computer to remember our work. But there is a difference between asking the computer to save a document and knowing that the save has finished. An application sends a request. Another component accepts it. A device may carry out work after that component has returned control to the user interface. Today we'll follow that request, look at its lifetime in C23, and learn why an accepted request must not disappear before its result has been collected.”

“Think of a note with the title ‘Monthly budget’. The note has a title, some text and a revision. We want the service to save 256 bytes from the document. The service cannot treat the request as a success simply because the button was clicked.”

**On screen:** Show the [request lifecycle diagram](../../assets/diagrams/device-io-request-lifecycle.svg).

## Submission — 1:15–3:30

**On screen:** Open `labs/native/io-request-lifecycle/device.h`, then `device.c`.

**Narration:**

“The first operation is Submit. Its inputs include the device model, a caller identity and a byte count. Its output is a new request ID. The word ‘output’ is important: we don't hand back a pointer to temporary storage. We return a value identifying the accepted request.”

“Before a request is accepted, the implementation checks whether the device is live, whether it is accepting new work, whether the byte count is within its limit and whether there is a free request record. These checks prevent an invalid request from partially changing the driver's state.”

**On screen:** Display:

```c
BtbDeviceStatus BtbDeviceSubmit(BtbDevice *device, uint32_t owner,
                                uint32_t bytes, uint32_t *outId);
```

**Narration:**

“Now inspect the statement that stores the new request. The request ID increases and a pending record remains in the device. No completion has been accepted yet. That is exactly why the application must not display a final success based on Submit alone.”

## Completion — 3:30–6:10

**On screen:** Open `labs/native/completion-queue/queue.c`.

**Narration:**

“The device may finish a request later. When it reports completion, our service checks the result and copies it into a completion queue. The queue has four slots. Each completion has a request ID, an outcome and a transferred-byte count.”

“This queue does not keep a pointer to the function's local result. It copies the result itself. That is a memory-ownership choice. A local function can return, but the stored result still exists.”

“Look at the capacity check. If all four slots contain uncollected completions, the next insertion returns FULL. That is not a reason to overwrite the oldest result. Every completion already accepted by the queue still belongs to the caller until it has been collected.”

**On screen:** Show the [four-slot ring](../../assets/diagrams/bounded-completion-ring.svg).

“Watch the head position. We add four completions, try to add a fifth, collect two, then add two more. The storage wraps around. The newest result does not push out an older one. This is what a bounded FIFO queue does.”

## Run the laboratory — 6:10–8:15

**On screen:** PowerShell with:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\completion-queue" `
    -B ".\output\learning-build\completion-queue" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\completion-queue" --parallel 2
ctest --test-dir ".\output\learning-build\completion-queue" --output-on-failure
```

**Narration:**

“CMake prepares the build. Ninja compiles the C code. CTest runs the executable checks. There are two tests in this small project: one verifies the FIFO operations and one executes the demonstration. Both should pass.”

“Now open `test_queue.c` and look at the full-queue assertion. The test checks not only that the fifth push fails, but also that the count remains four. The failure message is evidence of a refused action; unchanged state is evidence that no result was lost.”

## Connect to the real Kernel — 8:15–10:20

**On screen:** Show the header [`include/umicom/kernel/virtio_block.h`](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/virtio_block.h) beside the laboratory header.

**Narration:**

“The classroom model is intentionally simple. The real Umicom Kernel driver has to manage device-visible memory, transport descriptors, timeouts, completion checks and reset acknowledgement. A timer expiring does not prove that a device has stopped reading its queue memory. That distinction matters when deciding whether an allocated buffer can be released.”

“The Kernel also distinguishes successful completion of a write from the later FLUSH operation that provides a storage durability boundary when the backend honours that contract. So even the word ‘completed’ has to be interpreted in the context of the request and the guarantee we need.”

“We do not copy this classroom queue into the Kernel. The lesson helps us recognise and test the concepts already owned by the real driver.”

## Closing — 10:20–11:30

**On screen:** A sequence: `Submit → Pending → Complete → Collect → Release`.

**Narration:**

“A request becomes the driver's responsibility when it is accepted. A completion becomes the caller's responsibility when it is published. Only after the result has been collected can the driver release the completed request record in our model.”

“For the next lesson, trace a request when the user presses Cancel. Predict whether cancellation immediately frees the request. Then run the I/O request lifecycle test and compare your prediction with the actual result.”

**Reference:** [Bits2Banking](https://github.com/umicom-foundation/Bits2Banking) · [Umicom Framework](https://github.com/umicom-foundation/umicom-framework) · [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel)
