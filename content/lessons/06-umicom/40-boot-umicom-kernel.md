# Boot and inspect the original Umicom Kernel

An ordinary C application starts after an operating system has prepared a process, memory and services such as files and network sockets. A kernel is different: it forms part of the system that provides those services. Before calling a normal C function, the kernel must establish enough machine state for C code to run reliably.

You will follow the Umicom Kernel's actual RISC-V boot path, build its executable image and inspect its serial output in QEMU. This exercise runs in a virtual machine and does not install an operating system on your computer.

## 1. Distinguish Kernel, OS and Framework

The repositories have separate responsibilities:

| Repository | What it builds |
|---|---|
| [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel) | An original kernel research implementation: boot, privilege, memory, interrupts, scheduling and related mechanisms. |
| [Umicom OS](https://github.com/umicom-foundation/umicom-os) | Operating-system images, configuration, system integration, recovery and user-space components. |
| [Umicom Framework](https://github.com/umicom-foundation/umicom-framework) | Reusable application runtime, modules, GUI services, data services and adapters. |
| [Umicom Applications](https://github.com/umicom-foundation/umicom-applications) | Product applications composed from the Framework. |

The native kernel must not depend on the complete application Framework. A future Umicom System Services API provides a stable boundary between applications and kernel-specific adapters.

## 2. Why C cannot simply start by itself

At power-on or virtual-machine reset, a CPU begins executing from a firmware-defined entry point. It does not know about `main()` in a C program. It has not been given an ordinary program stack, heap or process environment.

The Umicom Kernel's initial architecture target is **QEMU RISC-V 64 `virt`**. Its boot entry is implemented in Assembly, and later execution enters C23 code.

```text
QEMU RISC-V virt machine resets
           │
           ▼
Machine-mode firmware entry
           │
           ▼
arch/riscv64/boot.S: _start
           │
           ├─ choose the boot hart (hardware thread)
           ├─ establish the bootstrap stack
           ├─ clear BSS (zero-initialised storage)
           └─ prepare the first C call
           │
           ▼
UmiKernelMain() in freestanding C23
           │
           ▼
Serial UART prints observable startup evidence
```

A **hardware thread**, often called a **hart** on RISC-V, is an independently executing processor context. **BSS** is the region containing global or static objects that begin as zero. A **linker script** tells the linker where the kernel's code and data must be placed in memory.

## 3. Find the real source files

Open the [kernel repository](https://github.com/umicom-foundation/umicom-kernel) or your checkout at `C:\umicom\umicom-kernel`.

The first-boot architecture separates these responsibilities:

```text
arch/riscv64/         Assembly entry and architecture-specific code
platform/qemu-riscv64/  QEMU machine peripherals and address constants
kernel/               Portable freestanding kernel logic
include/umicom/kernel/ Kernel contracts
```

This separation matters. A generic memory allocator should not contain hard-coded UART addresses belonging to one emulator machine. A device adapter owns those details.

For a code-level explanation of the actual entry sequence, read [`docs/FIRST_BOOT.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_BOOT.md). The milestone notes there describe the original first-boot stage; more recent kernel subsystems extend that stage rather than replacing the source history.

## 4. Configure the kernel build

Install the cross-compilation and QEMU tools described in the project's [Windows beginner setup](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WINDOWS_BEGINNER_SETUP.md). Once those dependencies are available, use the existing CMake preset:

```powershell
Set-Location "C:\umicom\umicom-kernel"

cmake --preset riscv64-clang-debug
```

The preset selects the expected RISC-V compiler, assembler, linker and build settings. Do not substitute an ordinary x86-64 compiler and expect the resulting executable to boot as RISC-V code.

## 5. Compile and test the kernel

```powershell
cmake --build --preset riscv64-clang-debug --parallel 2

ctest --preset riscv64-clang-debug --output-on-failure
```

A successful compile proves that the selected compiler and linker produced the requested files. It does **not** by itself prove that the kernel booted. That requires running it in the target machine environment and inspecting real output.

## 6. Start the kernel in QEMU

From `C:\umicom\umicom-kernel`, execute:

```powershell
& "C:\msys64\ucrt64\bin\qemu-system-riscv64.exe" `
    -machine "virt,aclint=off" `
    -bios ".\build\riscv64-clang-debug\bin\umicom-kernel.elf" `
    -display none `
    -monitor none `
    -serial stdio `
    -m 128M `
    -smp 1 `
    -no-reboot
```

`-machine` selects the virtual board. `-bios` loads the firmware-mode image at the start of this boot path. `-serial stdio` connects the virtual UART to the terminal so you can see early kernel messages. `-m 128M` provides 128 MiB of emulated RAM, and `-smp 1` starts with one virtual processor.

Do not change `-bios` to `-bios none -kernel ...` merely because it looks like a normal Linux command. The first Umicom Kernel machine-mode boot depends on the firmware entry behaviour documented in `docs/FIRST_BOOT.md`.

## 7. Understand the serial output

The original first-boot exercise prints a recognisable record containing values such as:

```text
UMICOM_KERNEL_BEGIN
name=Umicom Kernel
arch=riscv64
machine=qemu-virt
state=booted
UMICOM_KERNEL_END
```

The exact output can differ as later milestones add memory, traps, virtual address translation and diagnostics. A successful boot is established by the *current repository's acceptance checks*, not by insisting that a historical message is the only valid output.

If the terminal is silent, inspect the configured linker entry, firmware-loading mode, QEMU executable and serial configuration. Do not immediately assume that the C kernel function is wrong; the CPU may never have reached it.

## 8. Continue into real kernel subsystems

After startup, an operating system needs facilities for recovering from exceptions, receiving timer interrupts and controlling memory. Study the Umicom Kernel guides in this order:

1. [`TRAPS_AND_TIMER.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/TRAPS_AND_TIMER.md) — why a CPU transfers control when a trap occurs, and how time is measured.
2. [`PHYSICAL_MEMORY.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/PHYSICAL_MEMORY.md) — tracking pages that are free, reserved or owned.
3. [`VIRTUAL_MEMORY.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/VIRTUAL_MEMORY.md) — page tables and address translation.
4. [`HARDWARE_ADDRESS_TRANSLATION.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/HARDWARE_ADDRESS_TRANSLATION.md) — checking RISC-V Sv39 translation in hardware rather than only in a software simulator.

Schedulers, processes, kernel objects, IPC and device drivers are additional research topics. A booting image is an achievement with a precise scope; it is not yet a complete desktop operating system.

## 9. Try an investigation

Open `arch/riscv64/boot.S` and identify the instruction sequence that creates the first stack. Find the point where control passes to C. Then find the C code that prints to the UART. Draw the call and data flow between the Assembly entry, kernel code and QEMU peripheral adapter.

Do not edit the normal Umicom Kernel checkout for the first exercise. Use a separate practice copy if you want to test a deliberate failure. Once you understand the output, a small documentation correction or a new focused test can become your first kernel contribution.

Continue with [Assembly and processor contracts](../03-native-code/35-assembly-and-processor-contracts.md) or return to [Umicom OS](27-umicom-os.md).

## Continue with a connected course

[Hosted Kernel labs](../../courses/umicom-kernel-from-scratch/index.html) — Study bounded input and firmware contracts before machine boot experiments.

[Find prerequisites and other learning routes](../../start/systems-learning.md). Return to this chapter whenever the course refers to its concepts.
