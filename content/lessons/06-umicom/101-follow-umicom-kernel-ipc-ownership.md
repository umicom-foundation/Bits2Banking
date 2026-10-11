# 101. Follow IPC ownership through Umicom Kernel

The earlier C23 exercises build teaching models: a copied-message queue, a binary trace reader and a request dispatcher. We can now compare those models with an actual kernel implementation. Umicom Kernel is developed independently from the application Framework and starts on a QEMU RISC-V64 system.

The purpose of this lesson is to trace a message through the Kernel's source files and understand which subsystem is responsible for each safety decision.

## 1. Begin with the message-channel contract

Open [include/umicom/kernel/message_channel.h](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/message_channel.h).

This header defines paired message endpoints, bounded incoming queues and message handles. It distinguishes the **owner** of a handle from the receiver that owns a queue. A message is copied into the destination queue when a send is accepted. Closing one endpoint does not automatically delete bytes queued at the other endpoint.

Next open [kernel/message_channel.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_channel.c). Look for `UmicomKernelMessageSend`, `UmicomKernelMessageReceive`, `UmicomKernelMessagePeek` and `UmicomKernelMessageConsume`. Observe the functions that check handle generations, owner identity, rights and storage capacity.

A handle is not just an address. It is an opaque identifier whose meaning depends on a live Kernel-owned table entry. This prevents a process from gaining authority merely by guessing an integer or retaining a handle after it has been closed and replaced.

## 2. Find the syscall boundary

Open [kernel/message_service.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_service.c).

This module translates requests received through the Kernel's service interface into channel operations. Its user-buffer helpers inspect user virtual memory before copying. A user-space address is **not** automatically a valid machine-mode pointer.

Follow `UmicomKernelMessageServiceDispatch`, then inspect the copy helpers. The code checks the full destination span before delivering a received message. A failure in the second mapped page must not consume the message or modify the first page as a partial delivery.

The service binds to an authenticated process identity supplied by the Kernel's execution context. It does not accept an arbitrary caller identity from a request register as the authority.

## 3. Follow virtual-memory permissions

Open [kernel/user_memory.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c). Find `UmicomKernelUserMemoryCheck` and the page-record comparison beneath it.

The checker must confirm that a requested user byte span belongs to the caller's mapped address space, has suitable permissions and is backed by Kernel-controlled ownership information. Merely finding a translation in the page table is not sufficient if the mapping does not belong to the caller's approved page records.

This connects directly to the earlier lessons on [Sv39 translation](../05-engineering/89-sv39-virtual-address-translation.md) and [page faults](../05-engineering/93-understand-page-faults-in-c23.md).

## 4. Follow blocking operations

Open [kernel/user_ipc.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_ipc.c) and [include/umicom/kernel/user_ipc.h](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/user_ipc.h).

When a channel is not ready to complete a send or receive, a user task may wait. The pending SEND stores **copied data**; it must not borrow temporary bytes from a trap stack after the kernel returns to its scheduler. A pending RECEIVE retains an address value that is checked again before writing. A timeout or cancellation can end a wait that has not committed. It cannot retract a message that has already been accepted.

This is more involved than the four-slot FIFO in our lab. The real Kernel owns task records, deadlines, queue state and saved register frames, and it must make them consistent when a waiting task resumes.

## 5. Identify the remaining boundaries

This project targets RISC-V64 in QEMU. Its code and documentation describe a native, developing kernel; they do not imply that all Linux desktop applications, network devices, POSIX processes or symmetric multiprocessor configurations are supported.

In particular, the current IPC source describes operations serialised on one hart. That design is not automatically thread-safe in an unrelated multi-core application. Consult the current [Kernel capabilities guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/CURRENT_CAPABILITIES.html) and the [message-channel guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/MESSAGE_CHANNELS.md) before extending the implementation.

## 6. Explore the real project

If the RISC-V64 toolchain and QEMU are installed, follow the maintained [Kernel build and test guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md). Run the registered tests that correspond to the capability you are studying and record their results. If your environment does not provide the cross-compiler or emulator, source inspection and the hosted C23 laboratories are still valid exercises.

To practise source reading, make a four-column table with **API**, **owner**, **validation** and **failure behaviour**. Enter one row each for the channel send, channel receive, user-memory check and blocked receive. Explain which part copies bytes, which checks caller rights, and which decides whether a task is ready to run.

Finally compare the Kernel implementation with the [bounded channel laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/bounded-channel). Identify two protections the Kernel implements that the classroom queue intentionally does not.

Continue with the next operating-system course on process scheduling, resource handles and service supervision.
