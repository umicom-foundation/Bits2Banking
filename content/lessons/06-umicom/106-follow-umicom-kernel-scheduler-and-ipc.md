# 106. Follow scheduling and blocked IPC through Umicom Kernel source

So far, we have developed two portable C23 learning models: a ready queue and a service that waits for messages. We can now examine how similar concepts appear in the actual **Umicom Kernel**, which is a separate freestanding C23 and RISC-V Assembly project.

The Kernel has more responsibilities than our laboratory. It must maintain processor register state, protect user memory, identify the running task, validate message handles and make a blocked task runnable again when a legitimate operation completes.

## 1. Identify the project boundary

The authoritative source is the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel). It is not the Umicom Framework library and it is not the complete Umicom OS distribution. The native Kernel currently targets a research execution environment; do not infer hardware or full POSIX compatibility merely from source-code presence.

Find the files in your local checkout:

```text
C:\umicom\umicom-kernel\
├── kernel\
│   ├── user_scheduler.c
│   ├── user_ipc.c
│   ├── message_channel.c
│   ├── message_service.c
│   └── user_memory.c
├── include\umicom\kernel\
│   ├── user_ipc.h
│   └── message_channel.h
└── arch\riscv64\
```

## 2. Read the scheduler first

Open [`kernel/user_scheduler.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_scheduler.c). Locate its task state descriptions and the points at which it selects a runnable task. Ask these questions while reading:

1. Where is an admitted task kept before its first dispatch?
2. What identifies the task and prevents confusing it with a later task in the same slot?
3. Which saved state must survive a switch away from the task?
4. How does the scheduler distinguish a task that is blocked from one that simply exhausted its turn?

Do not assume that the laboratory's eight fixed slots or its handle encoding are public Kernel contracts. The exercise models concepts; the Kernel source defines its own rules.

## 3. Follow the message's owned bytes

Open [`kernel/message_channel.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_channel.c). Its source documents paired incoming queues, owner checks, rights and stale-handle rejection.

In the classroom programme, one successful send copies the bytes into `BtbChannel`. In the Kernel, copying is more demanding because a user programme cannot simply pass an arbitrary pointer into privileged code.

Open [`kernel/user_memory.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c). Notice that user virtual addresses must be checked against the address space, permissions and backing frame ownership. This is why the Kernel cannot treat a number supplied by user code as an unrestricted machine pointer.

## 4. Follow a blocked message call

Open [`kernel/user_ipc.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_ipc.c). Its ownership description identifies a particularly important distinction: a pending send retains **copied bytes**, while a pending receive retains a user address value to be validated again before the destination is written.

A wait record is not a temporary pointer into an invocation's trap stack. If the task blocks, the service must retain only state that stays valid until completion or cancellation.

The [Kernel blocking IPC guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BLOCKING_IPC.md)
explains two opt-in waiting calls: `MESSAGE_SEND_WAIT` and
`MESSAGE_RECEIVE_WAIT`. In its documented native RISC-V call convention,
register `a7` selects the operation while `a0`–`a3` carry arguments such as
an endpoint token, buffer address, capacity and relative timeout. A timeout
value of zero requests one immediate attempt; waiting requires an explicitly
selected nonzero or unbounded policy. The exact numbers and units belong to
the Kernel's own ABI and QEMU profile, **not** to the classroom trace.

The source describes a single-hart, serialised execution model for this subsystem. It is not evidence that its wait operations are automatically safe on several cores without additional synchronisation.

![A waiting task and copied channel bytes](../../assets/diagrams/blocking-ipc-wakeup.svg)

## 5. Understand the user/kernel boundary

Open [`kernel/message_service.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_service.c). This file turns checked user requests into message operations. Look for the flow from task identity to handle validation to checked user-buffer access, and then to successful publication or refusal.

Compare that sequence with [Lesson 100 — Design checked service requests](../05-engineering/100-design-checked-service-requests.md). The training dispatcher is hosted C23 and does not perform privileged transitions. The Kernel must also obey its architecture's trap and privilege protocol.

## 6. Build and validate the actual Kernel separately

The Kernel repository documents a RISC-V64 Clang/QEMU build. Start with its [build and test guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md) and [current capability map](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/CURRENT_CAPABILITIES.html).

After following the Kernel toolchain setup and confirming the QEMU dependencies, the normal PowerShell sequence is:

```powershell
Set-Location "C:\umicom\umicom-kernel"
cmake --preset riscv64-clang-debug
cmake --build --preset riscv64-clang-debug --parallel 2
ctest --preset riscv64-clang-debug --output-on-failure
```

These commands build and test the **Kernel repository**, not the hosted Bits2Banking teaching models. A successful local run qualifies only the configuration and tests actually executed. It does not establish general-purpose operating-system readiness.

## 7. Practise

Write down which component owns each of the following: the scheduled task's saved frame; the queued message's copied payload; the live message handle and its rights; the waiting receive's target address; the virtual-to-physical memory mapping. Compare your answers with the Kernel interfaces and source commentary.

Finally, read the [previous IPC ownership lesson](101-follow-umicom-kernel-ipc-ownership.md) and explain what the new blocking/wake-up layer adds beyond an ordinary nonblocking queue.
