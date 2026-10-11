# 116. Read Umicom Kernel interrupt ownership and recovery code

The previous lessons implemented classroom state machines and a read-only trace parser. Now we will inspect the actual Umicom Kernel implementation and identify which responsibilities are handled in RISC-V Assembly, which belong to C23, and which must be checked by a trusted Kernel caller.

No local teaching model should be linked into the Kernel as a substitute for its existing interrupt controller, timer, trap handler or process-management code.

## 1. Start from the real source tree

Open the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel). Work through these files in order:

| Source | What it teaches |
| --- | --- |
| [`docs/INTERRUPT_OWNERSHIP.md`](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/INTERRUPT_OWNERSHIP.md) | Nested critical sections, source leases and saved MIE policy |
| [`include/umicom/kernel/interrupts.h`](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/interrupts.h) | Public status types and ownership contracts |
| [`kernel/interrupts.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/interrupts.c) | Trusted C23 owner, token tracking, admission and refusal |
| [`arch/riscv64/trap.S`](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap.S) | Save the machine register frame at privileged entry |
| [`kernel/trap_guard.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/trap_guard.c) | Validate return control state and stop on corruption |
| [`kernel/user_ipc.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_ipc.c) | Retained user waits and cancellation boundaries |

The documents describe specific implemented research capabilities. A test passing in a classroom C23 application is not proof that the kernel has booted successfully on an emulated or physical machine.

## 2. Identify the register boundary

In RISC-V, `mstatus` contains the global machine-interrupt enable bit **MIE**. The `mie` register enables individual interrupt sources. Clearing global MIE can mask delivery without clearing a device's pending state. The Kernel must not confuse these operations.

The documented interrupt owner uses a RISC-V Assembly primitive to capture and clear the earlier MIE state together. A later restoration changes the relevant bit, rather than writing back an old snapshot of all `mstatus` fields. Restoring the whole word could overwrite state associated with a privilege transition or trap return.

Read [`arch/riscv64/trap.S`](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap.S) and locate `csrw mtvec, t0`, the instruction that installs a trap entry address. The file also defines how the integer-register frame is saved. C23 then operates on saved state; the compiler cannot be asked to create the very first machine trap frame by an ordinary function call.

## 3. Examine the C23 ownership policy

In [`kernel/interrupts.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/interrupts.c), find how the controller remembers:

- the owner of a nested critical section;
- the previous machine-interrupt enable condition;
- the issued token and nesting depth;
- the source lease and its owner;
- whether an unsafe state has poisoned the controller.

The production contract is **not** identical to our teaching trace: the Kernel has actual platform admission checks and a single trusted controller for its supported hart. It currently documents a narrowly supported machine-timer source, rather than promising a generic interrupt manager for every possible device.

A wrong-owner Leave or an out-of-order token must not restore interrupts accidentally. The caller must check the returned status and react safely.

## 4. Understand why a fault cannot be casually recovered

The classroom model has a `RECOVER` event, but real Kernel state can be harder to restore. In [`kernel/trap_guard.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/trap_guard.c), review the trap-frame checks, landing-stack sentinels and emergency-stop path.

When a frame is corrupt or trap nesting violates the documented entry contract, the Kernel does **not** simply clear a flag and retry user code. This is an essential difference from the `service-recovery` laboratory, which runs in an ordinary process and cannot inspect CPU privilege state.

Read the Kernel's [blocking IPC guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BLOCKING_IPC.md) to see how cancellation also depends on ownership. Pending sends retain copied bytes. Pending receives retain address values that are checked again before delivery. Cancelling an uncommitted request does not reverse a packet already accepted by a destination queue.

## 5. Build the actual Kernel separately

The Kernel is not a subdirectory of Bits2Banking. To qualify its current RISC-V build on a prepared Windows development computer, use the Kernel repository:

```powershell
Set-Location "C:\umicom\umicom-kernel"
cmake --preset riscv64-clang-debug
cmake --build --preset riscv64-clang-debug --parallel 2
ctest --preset riscv64-clang-debug --output-on-failure
```

Follow the actual [Kernel build and test instructions](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/BUILD_AND_TEST.md) before launching QEMU. The current Kernel profile uses the specified RISC-V `virt` machine and its own entry route; neither the teaching lab nor the Framework trace viewer is a bootloader.

## 6. Trace one end-to-end scenario

Write down what each component owns when a user programme waits for a message and a timer interrupts execution:

1. The CPU records trap cause and interrupted instruction address.
2. Assembly preserves the required register state.
3. Trusted C23 Kernel policy checks the caller, source and saved state.
4. The scheduler retains the user task's continuation.
5. The IPC subsystem owns copied message bytes or a validated pending operation.
6. A later wake-up makes work eligible; it does not guarantee immediate execution.
7. Return to user code is allowed only after the relevant safety checks.

**Practise:** Explain why a source lease is not a global capability, why MIE masking is not acknowledgement, why an error in the trap frame may require an emergency stop, and why a classroom test cannot qualify privileged code.

**Continue:** Return to the [Systems engineering course](../05-engineering/index.md) and use the two new C23 laboratories to practise explicit ownership and checked recovery.
