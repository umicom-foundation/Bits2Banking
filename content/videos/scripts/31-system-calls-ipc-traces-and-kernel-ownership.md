# Video 31 — System calls, IPC traces and Kernel ownership

**Duration:** Approximately 10–13 minutes  
**Lessons:** [99 — IPC traces](../../lessons/05-engineering/99-inspect-an-ipc-trace-with-c23.md), [100 — Service requests](../../lessons/05-engineering/100-design-checked-service-requests.md), [101 — Kernel IPC](../../lessons/06-umicom/101-follow-umicom-kernel-ipc-ownership.md)

## Scene 1 — A request needs permission (0:00–2:00)

**On screen:** [System-call boundary diagram](../../assets/diagrams/system-call-boundary.svg) with the user programme, trap boundary and kernel service.

**Narration:**

“In the previous video a Notes event moved through a copied-message queue. That was an ordinary C programme. An actual operating system has more to do: it must prevent one application from taking control of another application's memory or resources.

“When an application requests a kernel service, the request crosses a protected boundary. The application can ask, but it cannot declare itself authorised. The kernel knows which task is running, verifies the request arguments and resolves handles against its own records.

“On RISC-V, the `ecall` instruction requests an environment call. It is not a complete syscall API by itself. The software environment must define which operation number goes in which register, what the arguments mean and what result the caller can expect. The kernel must also have a trap handler to receive the request.

“We will not try to execute a privileged trap from our Windows demonstration. Instead, we will build a service model in C23 and read the real Umicom Kernel service code.”

## Scene 2 — Validate before changing state (2:00–4:30)

**On screen:** `labs/native/syscall-dispatch/dispatch.h`, `dispatch.c`, and `test_dispatch.c`.

**Narration:**

“The teaching dispatcher has two operations. One reads a fictional tick counter. The other writes a short Notes event to a fixed-capacity list.

“Before the write is accepted, the service checks that the request has the publishing right, that its expected revision still matches, that the text is a valid length and that another slot exists. It does not increase the revision or write partial text when one of those conditions fails.

“Open `test_dispatch.c`. The first call attempts to publish without a right. It is refused, and both the stored state and the output reply remain unchanged. Another call has the right but an outdated revision: it too is refused. Only the fully valid request changes the state.

“One crucial warning: our classroom programme receives a claimed caller ID and claimed rights in a simple struct. A real kernel must **not** trust those fields. It derives the current caller from protected execution state and checks live handles, permissions and address-space mappings.”

**On screen:** Run the build and CTest commands from Lesson 100. Show the training tick output and accepted event.

## Scene 3 — Read a trace without running it (4:30–7:00)

**On screen:** [Binary IPC trace diagram](../../assets/diagrams/ipc-trace-format.svg). Highlight offsets 0, 8, 10 and 12.

**Narration:**

“Developers need evidence of what their software attempted. We will inspect a small, invented trace format for training. It starts with an eight-byte signature and a version number. Then it records how many SEND and RECEIVE events follow.

“We do not load it as code. We do not trust its counts. We read bounded byte slices in C23 and check every declared length before accessing its payload. A SEND adds an outstanding sender-recipient pair. A RECEIVE must match the oldest outstanding SEND. The input is limited to one mebibyte, with at most 4096 records and 64 pending messages.

“Notice that parsing success says only that the bytes follow our **teaching format**. It does not prove that the kernel sent any real message, that the identities are genuine, or that an event was authorised. An authenticated operational trace requires more than a valid file header.”

**On screen:** Run these commands after building `umicom-education`:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Trace = ".\build\umicom-education\education-ipc-trace-test\fixture with spaces\owned messages.ipc"
& $Education ipc-trace --file $Trace
```

**Narration:**

“Our regression test created this file. The command reports four records, two sends, two receives, no pending messages and five bytes of copied payload. It explicitly states that no IPC or system call was executed.

“The unit test also tries damaged headers, invalid events, incorrect send ordering and a full pending-message queue. A good native parser must reject a bad record without publishing a partly valid report.”

## Scene 4 — Trace the real Kernel implementation (7:00–10:30)

**On screen:** A source-browser walkthrough of `kernel/message_channel.c`, `kernel/message_service.c`, `kernel/user_memory.c`, and `kernel/user_ipc.c` in the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel).

**Narration:**

“Now compare our models with real Umicom Kernel source. `message_channel.c` manages live endpoint handles and copied queues. `message_service.c` translates the currently admitted service request into rights-checked queue operations. `user_memory.c` verifies that a buffer belongs to the user address space and has suitable permissions. `user_ipc.c` coordinates blocked operations and resumption.

“Those files divide responsibility deliberately. An IPC queue cannot by itself validate whether a pointer from a user programme is mapped. A syscall adapter cannot safely hold a pointer to a temporary trap-stack buffer after its call returns. The user IPC layer therefore owns copied pending SEND bytes and rechecks deferred RECEIVE destinations before writing.

“Read the repository's message-channel and blocking-IPC documentation for the current contract and its limitations. The native Kernel remains a developing RISC-V64 project; the classroom tests are not proof that every kernel feature or every hardware configuration is production ready.

“Our next task is to become comfortable reading these ownership boundaries in source. The written lesson gives you a table to complete for each operation: who owns the data, who checks permissions, when the operation commits and what remains after failure.”

## Scene 5 — Put knowledge into practice (10:30–12:00)

**On screen:** Side-by-side test source, real Kernel source and Bits2Banking course index.

**Narration:**

“The most useful outcome is not memorising a particular syscall number. It is learning how to ask precise questions when you examine a system: Which memory belongs to this caller? Which handle grants a right? When is a message copied? Can a failed operation consume work? Can a waiting task safely resume?

“Try the two laboratories, change a training request and predict the result before running its tests. Then inspect the corresponding Umicom Kernel source and explain which responsibilities were intentionally omitted from the simpler exercise.

“These materials are available in the Bits2Banking educational repository and are linked to the original Umicom development projects. As you learn, improve a source explanation, add an accurate test or help someone else understand a difficult concept. Teaching is one of the ways knowledge becomes useful to the wider community.”

**Closing screen:** Bits2Banking learning website, Umicom Framework and Kernel links, and the motto **We Value Each Other and Together Everyone Achieves More.**
