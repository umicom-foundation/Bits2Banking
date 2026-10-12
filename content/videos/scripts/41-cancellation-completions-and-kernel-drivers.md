# Episode 41 — Cancellation, completion queues and safe driver shutdown

**Length:** approximately 11–15 minutes  
**Companion reading:** [Lesson 124](../../lessons/05-engineering/124-cancel-quiesce-and-release-device-work.md), [Lesson 125](../../lessons/05-engineering/125-inspect-device-io-traces-in-c23.md), [Lesson 126](../../lessons/06-umicom/126-follow-umicom-kernel-device-requests.md)

## A cancellation race — 0:00–2:30

**On screen:** A Notes editor with an unsaved change, followed by Save and Cancel actions.

**Narration:**

“Suppose a note-saving operation is still running when the user closes the document. The application asks to cancel. Does that mean the save was cancelled? Not necessarily. The device might have already finished, or it might continue for a short time before stopping. Cancellation is a request, not a terminal device result.”

“Here are two possible timelines. In the first, the cancellation request reaches the device in time, and the device confirms cancellation. In the second, the device finishes successfully before cancellation can be honoured. Both timelines begin with the same cancellation request, but they end with different completion results.”

**On screen:** Display the [cancel versus completion diagram](../../assets/diagrams/cancellation-and-device-reset.svg).

**Narration:**

“If our programme equates Cancel with a completed operation, it may release memory while a device still has access to it. If it equates Cancel with failure, it may tell the user that data was not saved even though the operation finished successfully. We need the actual result.”

## Follow the C23 code — 2:30–5:15

**On screen:** `labs/native/io-request-lifecycle/device.c`.

**Narration:**

“Look for `BtbDeviceRequestCancel`. It marks the request as cancellation requested but leaves the request pending. Look next at `BtbDeviceComplete`. A CANCELLED result requires the earlier request. A SUCCESS result can still be accepted after a cancellation request, because the device may have won the race. Failed operations report no successful bytes in this exercise.”

“Completion acceptance copies a value into our queue. The service changes the request to Completed only if the queue insertion succeeds. A full completion queue produces CAPACITY, and the request remains pending so the result can be retried after space becomes available.”

**On screen:** `BtbDeviceComplete` and `BtbCompletionQueuePush` side by side. Highlight the queue insertion before the state transition.

“This ordering gives us a practical rule: check that the next owner can accept the result before releasing the current owner. When we collect a completion, the queue removes its oldest result and the request record is released. The result remains available to the caller in copied storage.”

## Quiesce and release — 5:15–7:20

**On screen:** Step through `BtbDeviceQuiesce`, `BtbDeviceOutstanding` and `BtbDeviceRelease`.

**Narration:**

“To stop accepting new work, the service enters a quiesced state. Outstanding work is not discarded. Old pending requests may still finish, and completed results still need to be collected.”

“Now try to release the service immediately after quiescing, while the completion queue still contains results. The test expects BUSY. That is correct. Releasing a service is an ownership decision, not simply a change in how the interface looks.”

**On screen:** Show test output for the expected BUSY result and then a successful release after collection.

## Inspect a device I/O trace — 7:20–10:45

**On screen:** Windows PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
ctest --test-dir ".\build\umicom-education" `
    -R "^framework\.education\.device_io_trace" --output-on-failure
& $Education device-io-trace --file `
    ".\build\umicom-education\education-device-io-test\fixture with spaces\driver requests.dio"
```

**Narration:**

“The new Umicom Education command reads a synthetic file representing 27 device events. It does not run a driver. It checks that submitted requests have unique identities, completion records refer to pending requests, cancellation acknowledgements are justified and results are collected in completion order.”

“Notice that completion order may differ from submission order. Request 101 can complete before request 100. The queue preserves the order in which completions were accepted.”

“Now imagine a malformed record that tries to detach a device while a request is still pending. The inspector must reject the entire trace. It must not publish a partly accepted report.”

**On screen:** Show the test's mutation checks and the final CTest result. Explain that 20,000 deterministic mutations cover selected cases, not all possible corrupt files.

## The real device boundary — 10:45–13:20

**On screen:** The real [VirtIO block interface](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/virtio_block.h) and [implementation](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtio_block.c).

**Narration:**

“Umicom Kernel goes beyond our classroom model. The block driver owns device-visible queue and bounce frames. It cannot free those frames merely because a request timed out. It must wait until its protocol establishes that the hardware is no longer using them, including reset acknowledgement where required.”

“There is another distinction: a successful write operation and a durable storage guarantee are not identical. The Kernel documents an explicit FLUSH boundary for its writable VirtIO path. We must not claim that a classroom trace proves physical persistence or device recovery.”

**On screen:** Show the three states `NOT_SUBMITTED`, `SUBMITTED_UNCONFIRMED` and `COMPLETED` from `UmicomKernelBlockMutationOutcome`.

“These names explain what has actually been established. They prevent a developer from presenting an ambiguous success when the device may already have modified some data.”

## Closing exercise — 13:20–14:30

**On screen:** Three questions: ‘Can a cancelled request complete successfully?’, ‘When can a request record be freed?’, ‘What does a FLUSH confirm?’

**Narration:**

“Run the completion queue and I/O lifecycle laboratories. Write down when each owner may release its storage. Then inspect the real Kernel interface and identify one point where the Kernel requires a stronger guarantee than our simulator.”

“Those are the habits that turn individual C23 functions into reliable systems: know who owns every resource, know when a result is final, and test what happens when operations do not finish in the expected order.”

**Reference:** [Bits2Banking lessons](https://github.com/umicom-foundation/Bits2Banking) · [Umicom Framework](https://github.com/umicom-foundation/umicom-framework) · [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel)
