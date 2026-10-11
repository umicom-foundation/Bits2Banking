# 91. Follow the Umicom Kernel from Assembly to memory management

In earlier chapters you compiled C23, called Assembly, inspected ELF symbols and examined programme-header load plans. Now we can follow these ideas into the real Umicom Kernel project, which researches a native kernel for a future Umicom OS platform.

**Umicom Kernel is not the same thing as Umicom Framework.** Framework provides reusable services for applications. The freestanding kernel begins without a hosted operating system or Framework library. Umicom OS currently also has an independent Linux-libre distribution track; the original Umicom Kernel remains a distinct development path.

## 1. Locate the source files

Open the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel). Then study the following files in order:

| Source | What you will learn |
| --- | --- |
| [`arch/riscv64/boot.S`](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S) | Where `_start` reads the hart ID, prepares the stack and clears BSS |
| [`kernel/main.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/main.c) | The first C23 control path after early Assembly |
| [`kernel/physical_memory.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/physical_memory.c) | Reserved versus caller-owned RAM frames |
| [`kernel/virtual_memory.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtual_memory.c) | Three-level Sv39 page tables and software translation |
| [`docs/HARDWARE_ADDRESS_TRANSLATION.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/HARDWARE_ADDRESS_TRANSLATION.md) | How real RISC-V hardware tests a translated load/store |

Read each file's explanatory comments before the implementation. These comments distinguish what the code proves now from future kernel goals.

## 2. Follow the first instructions

In `boot.S`, find `_start`. The first operation reads `mhartid` to determine which processor hardware thread (hart) began the current execution. The boot path parks secondary harts until a later policy handles them. It disables interrupts while the early trap infrastructure is not yet ready, sets `sp` to the bootstrap stack and clears the BSS region.

The critical transition to C23 happens only after the stack and zero-initialised globals are ready. The source passes the hart ID through argument register `a0` and the device-tree pointer through `a1` to `UmiKernelMain()`.

In [Chapter 75](../05-engineering/75-abi-stack-and-calling-conventions.md), you learned how register usage is part of a calling convention. This is that concept applied at the point where there is no hosted C runtime to do the startup work for us.

## 3. Understand why the linker script matters

The first-boot learning image is linked to the QEMU RISC-V64 RAM layout. Its ELF entry symbol and load addresses must agree with the firmware-loading route. This is why [Umicom Kernel's First Boot guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_BOOT.md) distinguishes loading the ELF with QEMU `-bios` from trying to launch this particular machine-mode image as a normal `-kernel` payload with `-bios none`.

An ordinary Linux process loader has very different responsibilities from the QEMU firmware/boot hand-off. The [`umicom-education load-plan`](../05-engineering/87-read-elf-program-headers-and-load-plan.md) command inspects ELF programme headers; it does not replace the QEMU bootstrap or the operating-system loader.

## 4. Follow physical and virtual memory separately

Read `kernel/physical_memory.c` and identify the two bitmaps: reserved and allocated physical frames. This is the real counterpart to the [frame-pool laboratory](../05-engineering/88-physical-pages-and-frame-ownership.md). The allocator must reserve the kernel image and other protected boot memory before giving a physical frame to a caller.

Now read `kernel/virtual_memory.c`. A page table does not create a data frame simply because an entry points to it. Page-table frames and mapped data frames have **different owners**. Destroying an address-space hierarchy frees its page tables but must not silently free the data frames that the caller still owns. The [Sv39 laboratory](../05-engineering/89-sv39-virtual-address-translation.md) models only the index and mapping rules to make this difference visible.

Finally, compare the software page walk with the more advanced [hardware-backed translation guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/HARDWARE_ADDRESS_TRANSLATION.md). A software walk proves what *our code calculates*. A hardware-backed load/store additionally tests what *the processor actually performs* under the chosen CPU privilege and translation configuration.

## 5. Build the real kernel in its own repository

From Windows PowerShell, using the prerequisites in the [Umicom Kernel Windows setup guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/WINDOWS_BEGINNER_SETUP.md):

```powershell
Set-Location "C:\umicom\umicom-kernel"

cmake --preset riscv64-clang-debug

cmake --build --preset riscv64-clang-debug --parallel 2

ctest --preset riscv64-clang-debug --output-on-failure
```

A successful build should produce the kernel ELF image under the preset's `build/riscv64-clang-debug` directory. Use the real file path with `umicom-education binary`, `symbols` or `load-plan` to study its format. Some ELF images may not have the symbol metadata a particular inspector requires; programme headers and symbol tables are different facilities.

Before launching QEMU, read [the recurring build and test guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md). It contains the qualified command for the currently selected target, including the required RISC-V `virt` machine options. QEMU test success demonstrates a specific emulated configuration, not readiness for arbitrary physical hardware.

## 6. Exercise and source review

Find the exact part of `boot.S` that clears the BSS. Explain why global C variables that have no explicit initialiser must start as zero. Then locate the virtual-memory code that converts a physical address into a page-table PPN. Describe how a 4096-byte-aligned frame address becomes a PPN and is stored in PTE bits beginning at bit ten.

Next, answer a lifetime question: if a page-table hierarchy contains a mapping to a data frame owned by a Notes application, who should release the data frame when the hierarchy closes? The caller that owns that data frame, not the page-table hierarchy acting without the caller's permission.

## 7. Continue

The next phase will examine controlled page faults, address-space switching, user processes and native kernel interfaces. Each lesson should continue referring to tested Umicom Kernel source rather than replacing it with a second teaching-only kernel implementation.
