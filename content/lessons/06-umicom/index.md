# Developing with Umicom

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
