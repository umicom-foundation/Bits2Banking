# Developing with Umicom

## Find a route into these projects

If the terminology is new, begin with [applications, an OS and a kernel](../00-getting-started/07-applications-os-and-kernel.md). Then use the [connected learning map](../../start/systems-learning.md) to choose prerequisites and related chapters.

The browser courses provide guided routes through [Umicom OS](../../courses/umicom-os-from-scratch/index.html) and [Umicom Kernel](../../courses/umicom-kernel-from-scratch/index.html). Their hosted labs require introductory C and build-tool knowledge; they are not complete production-system courses.


Explore Umicom Framework, the Kernel, Umicom OS and real application source.

- [23. Introducing Umicom Framework and its architecture](23-introducing-umicom.md)
- [24. Prepare a computer for Umicom development](24-development-setup.md)
- [25. Build an application with Umicom Framework](25-use-the-framework.md)
- [26. Umicom Kernel: from boot instructions to operating-system services](26-umicom-kernel.md)
- [27. Umicom OS: the complete system above the kernel](27-umicom-os.md)
- [28. Umicom Applications: reuse one foundation in many products](28-umicom-applications.md)

[Explore the practical source files](../../labs/index.md)

## Visit the project repositories

Read the [Umicom project repository guide](../../umicom/repositories.md) to find the Framework, Kernel, OS, Applications and Studio repositories, their source files and their own build instructions. The educational examples reference these real implementations.

## Inspect real system and Framework source

- [40. Boot and inspect the Umicom Kernel](40-boot-umicom-kernel.md) — freestanding RISC-V Assembly and C23 under QEMU.
- [Prepare and run the native Umicom learning tools](../../umicom/native-education-tools.md) — inspect, build and preview the website.

## Physical memory, virtual memory and the native kernel

- [91. Follow the Umicom Kernel from Assembly to memory management](91-follow-umicom-kernel-memory-source.md) — study the real C23/Assembly boot path, physical-page ownership and Sv39 translation.
- [88. Allocate physical frames in a teaching model](../05-engineering/88-physical-pages-and-frame-ownership.md).
- [89. Translate a virtual address using Sv39](../05-engineering/89-sv39-virtual-address-translation.md).

## RISC-V privilege and process boundaries

- [96. Privilege, traps and Umicom Kernel](96-riscv-privilege-and-trap-boundaries.md) — understand machine, supervisor and user modes; examine the actual RISC-V Assembly bootstrap and Kernel C23 source.

## IPC and system-service ownership

- [101. Follow IPC ownership through Umicom Kernel](101-follow-umicom-kernel-ipc-ownership.md) connects the classroom channel and dispatcher to the actual Kernel message domain, syscall service, user-memory checking and blocked IPC tasks.

## Scheduler, blocking IPC and user-memory contracts

- [106. Follow Umicom Kernel scheduling and blocked IPC](106-follow-umicom-kernel-scheduler-and-ipc.md) — read the authoritative C23 Kernel scheduler, message-channel, memory and pending-call sources.


## Kernel timer interrupts and event ownership

- [111. Follow Umicom Kernel timers and events](111-follow-umicom-kernel-timers-and-events.md) — read the real RISC-V trap Assembly, C23 user scheduler, event owner and blocking IPC source, then compare the responsibilities with the hosted learning laboratories.

## Interrupt ownership and service recovery

- [116. Read Umicom Kernel interrupt ownership and recovery](116-read-umicom-kernel-interrupt-and-recovery.md) — follow `kernel/interrupts.c`, the RISC-V trap boundary, fault policy and cancellation ownership. Keep the classroom source-trace format separate from a real Kernel event log.


## Driver and interrupt internals

- [121. Follow real Umicom Kernel driver and interrupt boundaries](121-kernel-driver-and-interrupt-boundaries.md) — read the C23 and RISC-V Assembly implementation without replacing the authoritative Kernel services.


## Read Umicom Kernel block-device ownership

- [126. Follow device requests through Umicom Kernel](126-follow-umicom-kernel-device-requests.md) — compare classroom completions with the real VirtIO request, timeout, reset and FLUSH contracts.


## Device discovery and VirtIO in the actual Kernel

- [131. Follow device discovery and VirtIO ownership in Umicom Kernel](131-read-umicom-kernel-device-discovery.md) — read the real hardware catalogue, bus translation, transport qualification, device queue and reset contracts without changing the Kernel repository.


## Storage and filesystem source tour

- [136. Follow storage and file systems in Umicom Kernel](136-follow-kernel-filesystems-and-storage.md) — inspect real VFS path ownership, file services, RAMFS, FAT16 ordered updates and VirtIO flush boundaries.

## Service processes and streams

[Keep a service's process and streams under one owner](supervise-service-ownership.md) explains descriptors, child waiting and launch-error reporting before following the OS supervisor source.
