# From Assembly to the Umicom Kernel — video script

**Duration:** approximately 20–25 minutes

## Opening: 0:00–3:00

**Narration**

“Every ordinary application relies on an operating system for services such as memory, files and processes. A kernel is part of the machinery that provides those services. How, then, does kernel code begin when there is no ordinary process to start it? The answer starts with a processor, a firmware hand-off, and a few carefully chosen Assembly instructions.”

**On screen**

Show a diagram of applications above Framework, System Services and kernel adapters. Identify the separate Umicom Kernel and Umicom OS repositories.

## Registers and the first stack: 3:00–7:00

**Narration**

“Assembly describes individual processor instructions. On RISC-V, registers have names such as `a0` for an argument and `sp` for the stack pointer. A C function depends on an ABI that tells it where arguments, results and stack storage are located. The first boot code must establish those conditions before it calls C.”

**On screen**

Compare the C and Assembly two-number addition exercises. Follow the register names from the source. Emphasise that Windows x86-64 and Linux System V have different calling conventions, while RISC-V uses a different ISA.

## Walk through the Umicom boot path: 7:00–12:00

**Narration**

“Umicom Kernel's first execution target is the QEMU RISC-V 64 virtual board. QEMU resets its emulated machine, loads the selected firmware image, and transfers control to `_start` in our Assembly boot file. The code selects the first hardware thread, prepares stack storage, clears the region for zero-initialised variables, and enters freestanding C23 kernel code.”

**On screen**

Open the current source in `arch/riscv64/boot.S`, locate `UmiKernelMain()` and then find the QEMU UART adapter. The exact file revisions should be identified on-screen so viewers can follow the corresponding source version.

## Build and run in QEMU: 12:00–18:00

**Narration**

“Building a kernel image and proving that it boots are two different tests. Compilation checks the source and link configuration. Running QEMU proves that the emulator loaded the image and the CPU executed the expected instructions.”

**On screen**

Run `cmake --preset riscv64-clang-debug`, the build command, CTest and then the QEMU command from [Boot and inspect Umicom Kernel](../../lessons/06-umicom/40-boot-umicom-kernel.md). Show the real serial output, or clearly label a reproduced transcript if the lesson is recorded without a runnable emulator.

## Memory, interrupts and OS services: 18:00–22:00

**Narration**

“Once the first C function runs, the work has only begun. The kernel must handle traps and timer interrupts, track physical memory, create and validate page tables, and eventually support protected processes and interprocess communication. Each capability should be understandable and independently tested.”

**On screen**

Show links to the official Umicom Kernel guides on traps, physical memory, virtual memory and hardware-backed Sv39 address translation. Return to the boundary between Kernel, OS and Umicom Framework.

## Closing: 22:00–25:00

**Narration**

“The value of writing a kernel is not merely obtaining a boot message. It is understanding how the processor, machine code, memory and software contracts cooperate. The complete source and exercises are available through Bits to Banking and the Umicom Kernel repository. Try explaining the boot path to another learner before progressing to interrupts and memory.”

**On screen**

Display the course and repository references. End with “We Value Each Other and Together Everyone Achieves More” and “Service to Many Leads to Greatness”.
