# 96. RISC-V privilege levels and Umicom Kernel trap boundaries

We have built two C23 teaching models: a page-access checker and a process lifecycle. A real kernel needs the processor to enforce their rules. RISC-V provides **privilege levels**, **control and status registers** (CSRs), and instructions for transferring control into and out of exception handlers.

These concepts are important because a software check in an ordinary application cannot replace processor-enforced memory protection.

## 1. Three levels used in RISC-V systems

| Mode | Typical role | Example responsibility |
| --- | --- | --- |
| Machine (`M`) | Highest privilege for firmware and early machine setup | Initial boot, machine-level traps |
| Supervisor (`S`) | Operating-system kernel code | Process memory management and protected services |
| User (`U`) | Unprivileged application code | Editing notes or calculating a report |

Not every RISC-V processor implements every optional mode or extension. Umicom Kernel's initial execution profile uses QEMU RISC-V64 `virt`. The original first boot begins in **machine mode**, prepares a stack and transfers control to C23 before later milestones establish more advanced privilege separation.

## 2. Follow the first instruction

Open [arch/riscv64/boot.S](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S). Find `_start` and follow these steps:

1. `csrr s1, mhartid` reads the current hardware-thread identifier.
2. `bnez s1, .Lpark` keeps non-boot harts out of the shared early setup.
3. `csrw mie, zero` temporarily disables machine interrupts until handlers are ready.
4. `la sp, __stack_top` establishes the stack required by C functions.
5. The BSS-clearing loop initialises static zero-filled memory.
6. Arguments are placed into `a0` and `a1` before entering the C kernel function.

These are real instructions used by the original project. For complete context, read [First Boot](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_BOOT.md).

## 3. Understand translation control

Sv39 uses page tables to translate virtual addresses. On RISC-V64, the `satp` register selects the current supervisor address-translation context. The privileged instruction `sfence.vma` ensures appropriate ordering and invalidation when page-table mappings change.

The following Assembly is **illustrative**, not a complete runnable program:

```asm
# Supervisor-mode concept: establish a prepared address-space root.
# a0 must already contain a valid satp value created by trusted kernel code.
csrw satp, a0
sfence.vma
```

The instruction alone does not make unvalidated memory mappings safe. A real kernel must construct correct page tables, ensure ownership of their frames and arrange exception recovery if a translation fails. Review [Umicom Kernel's hardware-translation guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/HARDWARE_ADDRESS_TRANSLATION.md) for the project's qualified sequence and its boundaries.

## 4. Understand exceptions

When an application executes an `ecall` instruction or the processor detects a translation problem, control follows the configured exception path. The handler must capture enough state to explain why execution stopped and to decide what should happen next.

A trap is not the same thing as terminating the application. The kernel may service a valid request, repair a recoverable mapping or refuse a prohibited access. The original Umicom Kernel's [trap and timer guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/TRAPS_AND_TIMER.md) introduces the earlier exception-handling foundation.

## 5. Connect memory and process state

Suppose Umicom Notes tries to write to its read-only instruction page:

1. The attempted store refers to a virtual address.
2. The memory-translation hardware examines the active page-table permissions.
3. The store is rejected, and an exception is delivered to the configured handler.
4. Trusted kernel code determines whether the process is permitted to continue.
5. If the operation cannot be safely recovered, process policy may move the affected process into a terminal or error state.

This is the connection between the [page-fault laboratory](../05-engineering/93-understand-page-faults-in-c23.md) and the [process-state laboratory](../05-engineering/95-model-a-process-lifecycle-in-c23.md). The laboratories model separate pieces; a full kernel must enforce and coordinate them.

## 6. Build the actual kernel on your own host

On Windows, use the repository's documented RISC-V64 preset:

```powershell
Set-Location "C:\umicom\umicom-kernel"
cmake --preset riscv64-clang-debug
cmake --build --preset riscv64-clang-debug --parallel 2
ctest --preset riscv64-clang-debug --output-on-failure
```

Do not copy the sample `satp` instructions into your kernel as a replacement for its existing privilege and memory-management code. The source under `umicom-kernel` is authoritative; the course uses references and conceptual models to explain it. The CMake and QEMU requirements are described in [Build and Test](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md).

## 7. Review questions

What privilege mode does the first Umicom Kernel boot use? Why does `_start` establish a stack before calling C23? Which operation changes the supervisor translation root? Why is the return from a trap a kernel-controlled decision rather than something an ordinary application should do itself?

Next, continue exploring executable loading, address-space ownership and system calls through the [Umicom Kernel source](https://github.com/umicom-foundation/umicom-kernel) and future lessons in this series.
