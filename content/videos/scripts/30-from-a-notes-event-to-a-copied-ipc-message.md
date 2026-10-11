# Video 30 — From a Notes event to a copied IPC message

**Duration:** Approximately 9–12 minutes  
**Lessons:** [97 — Kernel services](../../lessons/05-engineering/97-how-programmes-request-kernel-services.md), [98 — Copied-message channels](../../lessons/05-engineering/98-build-a-copied-message-channel.md)  
**Source:** [Bits2Banking bounded-channel laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/bounded-channel)

## Scene 1 — Why a second application needs a message (0:00–1:30)

**On screen:** Umicom symbol, then two simple panels titled *Notes* and *Activity Report*. One displays “Save weekly report”; the other is initially blank.

**Narration:**

“When a note-taking application saves a document, we may want another application to learn that the document has changed. Perhaps an activity-report panel needs to show the latest event. In the first lessons we passed data between functions inside one programme. This time we want to understand what changes when data must move between separately running programmes.

“Every running process has its own memory rules. A memory address from one process does not automatically identify readable memory in another. Copying a numerical pointer into a message is not a reliable way to share a document. The sender could modify or release the memory; the receiving process might not have permission to access it.

“We will solve that problem with a very small copied-message channel in C23. We will deliberately keep the example to a few functions so we can inspect every important check.”

## Scene 2 — Explain ownership using the diagram (1:30–3:00)

**On screen:** [IPC message ownership diagram](../../assets/diagrams/ipc-message-ownership.svg). Highlight the sender buffer, the channel queue and the receiver buffer in turn.

**Narration:**

“Look at these three boxes. The sender owns the original Notes text. The channel accepts a **copy** of those bytes. The receiver gets another copy when it successfully receives the message. The arrows show the movement of information, not ownership of one shared pointer.

“This difference matters. A successful send must leave the sender free to reuse its original buffer. At the same time, a message must not disappear because a receive attempted to write into a buffer that was too small. Good interfaces state who owns the bytes, how large a message can be, and whether a failure changes anything.

“Our teaching queue has four slots, and each accepts at most 64 bytes. We are using a fixed size so a learner can count the storage and understand what happens when it fills.”

## Scene 3 — Build the programme (3:00–5:00)

**On screen:** Windows PowerShell in `C:\umicom\Umicom-Bits2Banking`. Slowly enter these commands; do not fast-forward compiler errors.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\bounded-channel" -B ".\output\learning-build\bounded-channel" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\bounded-channel" --parallel 2
ctest --test-dir ".\output\learning-build\bounded-channel" --output-on-failure
& ".\output\learning-build\bounded-channel\btb-bounded-channel.exe"
```

**Narration:**

“CMake reads our build definition and writes the Ninja build instructions. Ninja compiles `channel.c` into a library and links that library into the small Notes example and its tests. We run CTest before trusting the demonstration.

“Now the programme sends a Notes event from training sender eleven to receiver twenty-two. Notice the code changes the first byte of the original sender buffer after sending. The printed message still begins with ‘Notes’. That is direct evidence that our queue stored its own copy.

“We have not created separate operating-system processes. We are studying the data-ownership rule in one ordinary application before involving protected process boundaries.”

## Scene 4 — Refuse an unsafe receive (5:00–7:30)

**On screen:** `channel.h`, `channel.c`, then `test_channel.c`. Highlight `BtbChannelReceive` and `BTB_CHANNEL_SMALL_BUFFER`.

**Narration:**

“Suppose the queued message is four bytes long. The receiver provides room for only three. A weak implementation might remove the queued message and then discover it cannot deliver the bytes. That turns an ordinary input mistake into lost information.

“Our function checks the requested recipient and the destination capacity **before consuming anything**. If the recipient is wrong, it returns Denied. If the buffer is too small, it returns Small Buffer. In either case, the original queued message remains available.

“After those checks succeed, the function copies the complete message to the receiver, publishes the sender and message sequence, clears the old queue slot and advances the FIFO head. The tests check these paths. They also fill all four slots and show that a fifth send is refused rather than replacing an earlier message.

“Try changing the receiver number in the example. You should be able to predict the refusal before running the programme. That is one of the best ways to understand an interface: identify its promises, predict its behaviour and then verify those promises with tests.”

## Scene 5 — Connect the example to Umicom Kernel (7:30–10:00)

**On screen:** Real [message_channel.h](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/message_channel.h), [message_channel.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_channel.c) and [message_service.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_service.c) in the source browser.

**Narration:**

“The actual Umicom Kernel implements protections that our hosted exercise does not. It uses endpoint handles, records who owns a handle, checks rights and rejects stale generations. Its message-service adapter validates user memory before copying bytes.

“A process cannot simply write ‘I am another process’ into a message and gain its authority. The kernel identifies the running task and looks up a live, rights-checked reference. The code is also careful about retaining a message when a receive cannot complete.

“Some operations may wait for a message or for space in the queue. The `user_ipc.c` module works with task scheduling and timeouts, and therefore needs a stronger lifetime model than our four-slot classroom example.

“Open the written lessons for the commands, source links and exercises. In the next video we will see how the processor's environment-call boundary connects requests to those protected kernel services, and how we can inspect a safe trace of fictional message events.”

**Closing screen:** Bits2Banking learning website, lessons 97–98, Umicom Kernel message-channel source, and the motto **Service to Many Leads to Greatness.**
