# 121. Follow real Umicom Kernel driver and interrupt boundaries

Our previous chapters built small C23 models of interrupt ownership, driver
lifetimes and diagnostics. We can now see how these concepts appear in the
actual Umicom Kernel repository.

Umicom Kernel is a freestanding operating-system kernel under development.
Its first target is the RISC-V64 `virt` machine in QEMU. Its privileged code
must manage hardware state and user/kernel boundaries that ordinary Windows or
Linux programmes are not permitted to access directly.

## 1. Find the source code

The kernel is maintained separately from Umicom Framework and Bits2Banking:

[Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel).

Start with these source files:

| Source | Responsibility |
|---|---|
| [`arch/riscv64/trap.S`](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap.S) | Enter an exception or interrupt and preserve processor state in Assembly. |
| [`kernel/interrupts.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/interrupts.c) | Coordinate machine interrupt delivery and source leases in C23. |
| [`kernel/trap_guard.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/trap_guard.c) | Check protected trap entry and return state. |
| [`kernel/virtio_block.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtio_block.c) | Implement the Kernel's device-specific VirtIO block foundation. |
| [`kernel/user_ipc.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_ipc.c) | Coordinate user-task waits and copied-message ownership. |
| [`kernel/events.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/events.c) | Remember event signals and coordinate waiters with the scheduler. |

Read the [Kernel interrupt ownership guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/INTERRUPT_OWNERSHIP.md)
before changing any privileged behaviour.

## 2. Trace a hardware timer event

The first steps take place at the processor level. A hardware event causes
RISC-V to record trap information in special control and status registers
(CSRs). The processor changes execution flow to the installed trap entry.

The trap entry must then save the integer register values before ordinary C23
can safely inspect the event. The code that saves and restores that context is
Assembly: `trap.S`. The C23 implementation decides what action is permitted.

The following is a conceptual overview rather than a statement that every
interrupt source is currently supported:

```text
Hardware source
    ↓
RISC-V privileged trap entry (Assembly)
    ↓
Protected register/CSR snapshot
    ↓
C23 validation and handler policy
    ↓
Acknowledge or reject according to source ownership
    ↓
Restore the allowed execution state
```

**Masking**, **acknowledging** and **releasing** an interrupt source are
separate operations. Masking controls delivery. Acknowledging records or clears
an observed event as required by the device protocol. Releasing ends a lease
only when the device and its handler are quiescent.

## 3. Why nested critical sections are difficult

Imagine a source owner calling a helper that also needs protection:

```text
Owner enters protected section
  Helper enters its own nested section
  Helper returns and leaves its section
Owner completes its update
Owner leaves the final outer section
```

The helper must not re-enable machine interrupts before the outer owner has
finished. The real Kernel controller records the nesting order and restores the
previous delivery state only after a matching outer leave. Its source lease
model stops another trusted service from borrowing the timer at the same time.

These guarantees are scoped to the documented hart and execution assumptions.
They are not claims of arbitrary SMP locking or general interrupt-driver
compatibility. For the precise constraints, read the actual Kernel guide.

## 4. Understand recovery boundaries

A hardware fault may leave several different objects involved: the interrupt
controller, a device-specific driver, a waiting user task and an application.
They do not all own the same state.

The driver may need to stop issuing work; the Kernel may need to preserve a
retained task frame; and the application may need a way to distinguish accepted
requests from requests that must be retried. An educational trace can help us
analyse this sequence, but it cannot substitute for the driver-specific
recovery procedure.

The [Kernel's current capability guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/CURRENT_CAPABILITIES.html)
distinguishes the capabilities that exist in the research profile from those
needed by a complete operating system. Successful QEMU tests do not imply
support for arbitrary physical computers or drivers.

## 5. Build the Kernel without modifying it

From PowerShell, in the separate Kernel checkout:

```powershell
Set-Location "C:\umicom\umicom-kernel"
cmake --preset riscv64-clang-debug
cmake --build --preset riscv64-clang-debug --parallel 2
ctest --preset riscv64-clang-debug --output-on-failure
```

The active RISC-V QEMU profile and host prerequisites are described in
[`docs/BUILD_AND_TEST.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md).
Do not assume a native Windows kernel executable will run directly: the
RISC-V64 image targets a different machine architecture.

## 6. Your turn

1. Find `UmicomKernelCriticalSectionEnter` and its matching Leave operation
   in the real Kernel header and source. What does the owner identity mean?
2. Find the RISC-V Assembly instruction that installs a trap vector in `mtvec`.
3. Follow the path from the saved trap context to the C23 policy code.
4. Explain why a diagnostic ring in user space cannot authorise Kernel recovery.
5. Read the `virtio_block.c` header comments. Which features belong to the
   hardware adapter, and which belong to the broader storage service?

Continue with the companion
[video on driver lifetimes and evidence](../../videos/scripts/39-driver-lifetimes-and-retained-evidence.md)
and the earlier [interrupt ownership lesson](../05-engineering/112-interrupt-ownership-and-critical-sections.md).
