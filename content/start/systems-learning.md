# Find your way from first concepts to OS and Kernel

Choose by what you want to understand, not by age or job title. You can return to a simpler explanation whenever it helps. Lessons explain one topic; courses arrange topics into a longer route.

## I am starting with no computing background

Begin with everyday ideas and paper activities. No installation is required. Read at your own pace; a learner can speak, draw or write an answer.

1. [Introduction to Computers](../courses/learning-computer-architecture/index.html) — Eight lessons from following a page to understanding what an operating system does.
2. [Inside a computer](../lessons/01-computers/01-inside-a-computer.md) — Meet physical components after practising input, rules and output.
3. [Bits and digital logic](../lessons/01-computers/02-bits-and-logic.md) — Explore how a shared interpretation turns patterns into information.
4. [The processor and memory](../lessons/01-computers/03-cpu-and-memory.md) — Follow a sequence of instructions and distinguish working memory from storage.

## I want to write my first program

Begin with [Learning C: For beginners](../courses/learning-c/index.html): eleven detailed lessons, paper tracing and an optional hosted lab.

First practise giving clear instructions. Then learn one command environment and one language. Reading the concepts does not require installing every tool.

1. [Turn a problem into steps](../lessons/02-programming/04-problems-and-algorithms.md) — Develop an algorithm, choose examples and predict results.
2. [Commands in PowerShell](../lessons/02-programming/05-powershell.md) — Use this route on Windows; understand the working folder and each command before running it.
3. [Commands in Bash](../lessons/02-programming/06-bash.md) — An alternative shell route for a suitable environment, not a prerequisite to finish PowerShell.
4. [Write a program in C](../lessons/03-native-code/09-c.md) — Learn source code, functions and values through a note-saving program.
5. [Write safer C23](../lessons/03-native-code/36-safer-c-programming.md) — Practise checking inputs and errors before a systems lab.
6. [Pointers and borrowed memory](../lessons/03-native-code/67-pointers-and-borrowed-memory.md) — Prepare for buffer and lifetime discussions in the Kernel course.
7. [Compilers, CMake and tests](../lessons/05-engineering/18-build-and-tests.md) — Understand which stage prepares, compiles, links or checks a program.

## I want to build an application with Umicom Framework

Follow [Umicom Framework Development](../lessons/umicom-development/index.md) to connect introductory C, installed libraries, CMake and a GTK4 window. The console and window share one checked function so you can see which code belongs to the application and which comes from Framework. The [Windows guide](../umicom/windows-development.md) explains the tool setup and separate configure, build, test and launch stages.

## I want to understand Umicom OS

Umicom OS includes a Linux-based image foundation and Framework-backed user-space software. Begin with its role, then read the course's source exercises. Hosted lab checks do not establish that a guest or physical computer boots.

1. [Meet the Umicom projects](../lessons/06-umicom/23-introducing-umicom.md) — Understand why reusable Framework services and applications are separate.
2. [The system above the kernel](../lessons/06-umicom/27-umicom-os.md) — Connect files, processes and services to the purpose of an OS.
3. [Prepare a development computer](../lessons/06-umicom/24-development-setup.md) — Use only when ready for practical builds; check current repository prerequisites.
4. [Umicom OS from Scratch](../courses/umicom-os-from-scratch/index.html) — Initial source-reading and hosted labs on startup plans, recovery, image identity and guest checks.
5. [System administration](../lessons/05-engineering/20-system-administration.md) — Learn the distinction between using a system and managing its configuration.

## I want to understand Umicom Kernel

The native Kernel is a separate project. Follow the first four sections of the foundation route and introductory C before its practical exercises. Use the subject links below to return to a concept as it appears in the source.

1. [What a kernel does](../lessons/06-umicom/26-umicom-kernel.md) — Understand privilege and the difference between the host and target machine.
2. [From the first instruction to a kernel](../lessons/01-computers/54-from-first-instruction-to-kernel.md) — Follow the startup idea before studying machine-specific details.
3. [Umicom Kernel from Scratch](../courses/umicom-kernel-from-scratch/index.html) — Read and exercise bounded input and firmware-memory contracts using real Kernel source.
4. [Boot and inspect the research Kernel](../lessons/06-umicom/40-boot-umicom-kernel.md) — A later, tool-dependent exercise; follow the exact supported machine profile.
5. [Memory management in the source](../lessons/06-umicom/91-follow-umicom-kernel-memory-source.md) — Connect locations, page ownership and translation.
6. [Privilege and traps](../lessons/06-umicom/96-riscv-privilege-and-trap-boundaries.md) — Understand controlled entry when execution needs Kernel attention.
7. [Messages between processes](../lessons/06-umicom/101-follow-umicom-kernel-ipc-ownership.md) — IPC means inter-process communication; follow who owns each message.
8. [Scheduling and waiting](../lessons/06-umicom/106-follow-umicom-kernel-scheduler-and-ipc.md) — Study how a process waits for work and later resumes.
9. [Timers and events](../lessons/06-umicom/111-follow-umicom-kernel-timers-and-events.md) — Follow timed work and the event owner.
10. [Interrupts and recovery](../lessons/06-umicom/116-read-umicom-kernel-interrupt-and-recovery.md) — Read the response to interruptions and faults.
11. [Drivers and interrupt boundaries](../lessons/06-umicom/121-kernel-driver-and-interrupt-boundaries.md) — Connect the device to the software responsible for it.
12. [Device requests](../lessons/06-umicom/126-follow-umicom-kernel-device-requests.md) — Trace a request through completion, timeout and reset.
13. [Device discovery](../lessons/06-umicom/131-read-umicom-kernel-device-discovery.md) — Compare firmware information with supported device bindings.
14. [Filesystems and storage](../lessons/06-umicom/136-follow-kernel-filesystems-and-storage.md) — Connect named files to storage and ownership.

## Ready for a practical lab?

Before building, explain a file path, a C function, an array, a return value and the difference between a compiler and a test. The Kernel labs also need bounds and pointer-lifetime concepts. If any are unfamiliar, return to the first-programming route.

[Course library](../courses/index.html) · [Guide for a learning companion](../teaching/support-first-time-learners.md)
