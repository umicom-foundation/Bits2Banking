# Preserve register values when execution is interrupted

Read a real Umicom trap entry a few instructions at a time. Learn how it switches to owned storage, saves the interrupted values and checks the return path before continuing.

## 1. What is being interrupted?

A processor executes instructions using small storage locations called **registers**. A register may hold a number, an address or an intermediate result. An **interrupt** asks the processor to handle an event such as a timer. An **exception** is caused by the current instruction, such as an invalid access. Both can enter a **trap handler**, the code responsible for deciding what happens next.

The interrupted computation still needs its register values if it is going to continue. The handler also needs registers for its own work. Saving the first set in memory lets it use the registers without silently changing the interrupted computation.

## 2. Learn the few names used here

| Name | Meaning in this source |
| --- | --- |
| `sp` | The stack pointer, a register naming the current stack location. |
| `ra` | The return address used by ordinary function calls. |
| `t0`, `t1` | Temporary integer registers; their interrupted values still need preservation. |
| `a0` | A register used for the first function argument and commonly for a return value. |
| `mscratch` | A machine control/status register used here to hold the prepared trap landing pointer. |
| `mepc`, `mcause` | Machine control/status registers containing the saved instruction address and trap cause. |

**Machine mode** is a privileged execution level. A **control/status register**, or CSR, controls or reports processor state. It is different from a byte stored at an ordinary memory address. This lesson follows Umicom's machine handler; user and supervisor handlers have their own entry paths.

## 3. Switch stacks before using the interrupted stack

Open [`arch/riscv64/trap_entry.S`](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/trap_entry.S). Find `UmicomRiscvMachineTrapEnter`:

```text
csrrw sp, mscratch, sp
addi sp, sp, -UMICOM_TRAP_INTEGRITY_FRAME_BYTES
sd t0, 32(sp)
```

`csrrw` reads the old CSR value into its destination register and writes the original source-register value into the CSR. Here the destination and source are both `sp`, so the instruction exchanges the two values. The [RISC-V Zicsr specification](https://docs.riscv.org/reference/isa/_attachments/riscv-unprivileged.pdf) defines this single-instruction exchange.

Before entry, Umicom has prepared `mscratch` with its dedicated landing address. After the exchange, `sp` contains that trusted address and `mscratch` holds the interrupted stack pointer. The old pointer is preserved as a number; the handler does not use it to choose where to save its frame.

 <svg viewbox="0 0 700 110" role="img" aria-label="The interrupted stack pointer is kept as a value while the handler switches to a separately prepared stack." style="width:100%;max-width:700px"><title>The interrupted stack pointer is kept as a value while the handler switches to a separately prepared stack.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Interrupted sp</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Swap with mscratch</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Owned trap stack</text></svg>

The interrupted stack pointer is kept as a value while the handler switches to a separately prepared stack.

## 4. Trace addresses without running privileged instructions

For arithmetic only, suppose the prepared top address is `0x80010000`. The prefix `0x` means hexadecimal, a base-16 way to write numbers. The frame size is 288 bytes, or `0x120`, from [`trap_integrity.h`](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/riscv64/trap_integrity.h).

1. After the swap, `sp = 0x80010000`.
2. `addi` adds a fixed immediate value: subtracting 288 gives `sp = 0x8000FEE0`.
3. `sd t0, 32(sp)` stores eight bytes containing `t0` at `0x8000FF00`.

Those addresses illustrate the calculation; they are not instructions to write to those locations. `32(sp)` means “the address in sp plus 32 bytes.” `sd` is a doubleword store on RV64. The later `ld` instruction loads eight bytes back. The source places `ra` at offset 0, the original `sp` at offset 8 and `t0` at offset 32.

## 5. Why save a temporary before using it?

The handler saves `t0` before loading an emergency handler address into it. “Temporary” describes a function-call convention; it does not mean an interrupted computation can lose the register at an arbitrary instruction.

After the integer registers and selected CSRs are saved, the Assembly places the frame address in `a0` and calls `UmicomRiscvMachineTrapDispatchGuarded`. The C wrapper checks the frame and the dispatcher's permitted changes. Compile-time offset assertions in the header also check that the C structure and Assembly byte positions agree.

## 6. A trap return is different from an ordinary return

On the checked return path, Umicom restores the saved registers and writes the approved instruction address to `mepc`. It restores `sp` last, then executes `mret`. Unlike ordinary `ret`, `mret` restores trap-related execution state and resumes at `mepc`. The [machine-level specification](https://docs.riscv.org/reference/isa/priv/machine.html) defines the privilege and interrupt-state changes.

This implementation uses a separate emergency vector while the first frame is live. A second fault stops through dedicated emergency storage instead of overwriting the first frame. It is a single-hart, non-nesting design with explicit assumptions about intact Kernel memory. Do not generalize it to every multiprocessor or nested-interrupt system.

## 7. Exercises using the actual source

1. Locate the store and matching load for `a0`. Verify that both use offset 72.
2. Find where the original `sp` is read from `mscratch` and stored at offset 8.
3. Explain why saving `t0` after overwriting it would lose information.
4. Read one `_Static_assert` in the header. Explain how a disagreement can be caught during compilation.

<details>

<summary>Check the reasoning</summary>

The handler cannot restore a value it never saved. Matching byte offsets preserve register identity. The static assertion compares the C field's actual offset with the Assembly contract; a changed structure layout must not silently restore one register from another register's slot.

</details>

Continue with [Umicom Kernel from Scratch](../../../courses/umicom-kernel-from-scratch/index.html). Reading or tracing this lesson does not count as executing the trap or qualifying physical hardware.

---

[Read this lesson in HTML](../../../courses/learning-riscv-assembly/lessons/03-preserving-interrupted-registers.html) · [Learning sequence](../../../start/learning-sequence.md)
