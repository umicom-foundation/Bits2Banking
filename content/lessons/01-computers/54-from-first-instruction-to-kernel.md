# 54. From the first machine instruction to Umicom Kernel

A normal C program begins after an operating system has created a process, supplied memory and prepared an execution environment. A kernel is different: it helps establish the environment in which ordinary programs will later run.

To understand the difference, compare the C-and-Assembly function from the previous lesson with the first boot of the [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel).

## 1. Understand what happens before `main`

When you launch the C23 Assembly demonstration on Windows, the operating system loads an executable file and prepares the process. Runtime startup code eventually calls `main`. Memory and an initial stack are already available. Operating-system services make console output and file access possible.

At the start of an original kernel, many of those services do not yet exist. The kernel cannot assume that it can call an ordinary C library function to print to a Windows terminal or open a file. Its first instructions must work with the execution conditions established by its firmware or boot protocol.

This is called a **freestanding environment**. The initial Umicom Kernel research target is RISC-V64 under QEMU's `virt` machine. Read the real [First Boot guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_BOOT.md) alongside this lesson.

## 2. Inspect the entry point

The Umicom Kernel's early boot instructions are in [`arch/riscv64/boot.S`](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S). Assembly is appropriate there because the initial code must interact with processor registers, initialise a stack, prepare memory and transfer control into C23 without depending on a hosted C runtime.

The first educational boot sequence establishes the following chain:

```text
QEMU resets a simulated RISC-V machine
    |
    v
Firmware/boot hand-off
    |
    v
_start (RISC-V Assembly)
    |
    +--> Establish the stack
    +--> Clear the BSS area
    |
    v
UmiKernelMain() (freestanding C23)
    |
    v
Write evidence to the simulated serial device
```

`_start` is an entry symbol in the native executable. **BSS** is a region for static objects whose initial value is zero. The **stack** is temporary memory used for function calls and local state. Clearing BSS matters because C programs expect zero-initialised static data to begin at zero, even though there is no ordinary operating-system loader to prepare it for this kernel.

A **serial device** is a hardware interface that sends and receives bytes. In QEMU, a simulated serial port is a convenient way to report early boot progress before any graphical desktop exists.

## 3. Understand the linker script

Assembly source tells the processor which instructions to execute. A **linker script** tells the linker where important code and data sections should be placed in the kernel's memory image.

For the first Umicom Kernel boot profile, the documented RISC-V machine begins its kernel-owned region at hexadecimal address `0x80200000`. The first 2 MiB of QEMU's example RAM layout is outside that region. The linker must not incorrectly claim all 128 MiB of RAM above `0x80200000`.

This is not a universal RISC-V address. It belongs to this specific educational QEMU profile. Later architectures and boot mechanisms may have different layouts.

## 4. Build and test in the real Kernel repository

The Kernel repository is separate from Umicom Framework and Bits2Banking. On your Windows development computer, its own build documentation shows the required toolchain setup and CMake preset.

Once the prerequisites from [Windows beginner setup](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WINDOWS_BEGINNER_SETUP.md) are installed:

```powershell
Set-Location "C:\umicom\umicom-kernel"

cmake --preset riscv64-clang-debug
cmake --build --preset riscv64-clang-debug --parallel 2
ctest --preset riscv64-clang-debug --output-on-failure
```

CMake and Ninja generate an ELF file, but **producing an ELF file is not proof that the kernel boots**. The next separate acceptance step is to start the resulting kernel image in QEMU and examine the serial output. Use the exact launch command in [the current Kernel build and test guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md).

The original first-boot profile uses QEMU's `-bios` option to enter its machine-mode ELF. Do not assume that `-bios none -kernel ...` is an equivalent launch path; the first-boot guide explains the different reset and firmware hand-off behaviour.

## 5. Learn the next kernel responsibilities

Booting into C is only the beginning. A useful kernel eventually needs to manage exceptions, timers, memory ownership, virtual addressing, privilege levels, processes and device access. Study the actual Umicom Kernel documents in this order:

- [Traps and timer interrupts](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/TRAPS_AND_TIMER.md): what the processor does when execution is interrupted or an exception occurs.
- [Physical memory](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/PHYSICAL_MEMORY.md): how the kernel tracks which physical pages are available or reserved.
- [Virtual memory](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/VIRTUAL_MEMORY.md): how virtual addresses correspond to physical pages.
- [Hardware-backed address translation](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/HARDWARE_ADDRESS_TRANSLATION.md): how RISC-V Sv39 mappings are tested by the processor itself.

Each resource describes a different capability and its validation limits. Do not treat an implemented page-table test as proof that a complete filesystem, graphical desktop or production-ready kernel exists.

## 6. Try it yourself

Draw the boot sequence in your notebook. Mark the moment when Assembly hands control to C. Then find where the first Umicom Kernel serial output is produced. Which portion is processor-specific? Which portion could be reused on a different processor?

Make a short comparison between an ordinary application and a freestanding kernel: Who provides the initial stack? Who establishes the output device? What does the linker control? What additional test is required after compiling the kernel image?

Finally, explain in your own words why **Umicom Kernel**, **Umicom OS** and **Umicom Framework** are different projects. Umicom Kernel develops original native-kernel mechanisms. Umicom OS packages operating-system services and user-space components and can target different kernels. Umicom Framework provides reusable application capabilities above those system boundaries.

## Continue with a connected course

[Read the native Kernel source](../../courses/umicom-kernel-from-scratch/lessons/01-native-kernel-and-host-models.html) — Distinguish host checks from target-machine execution.

[Find prerequisites and other learning routes](../../start/systems-learning.md). Return to this chapter whenever the course refers to its concepts.
