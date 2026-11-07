# Learning RISC-V Assembly

Relate RISC-V instructions and register conventions to real Kernel and Framework sources.

Read Learning RISC-V and the first three Assembly lessons. Then trace a function and its calling convention.

[Browser course](../../../courses/learning-riscv-assembly/index.html) · [Choose a subject](../../../start/course-series.md)

## Reading order

1. [Follow a system call from C into Assembly](01-follow-a-system-call.md)
2. [Understand entry, return and program exit](02-entry-return-and-exit.md)
3. [Preserve register values when execution is interrupted](03-preserving-interrupted-registers.md)
4. [Trace a leaf function](04-trace-a-leaf-function.md)

## Course outline: later topics

Loads, branches, ABI preservation, traps and emulator debugging.

Read one topic at a time. The list above links to available lessons; the outline describes further study. Each practical lesson gives its own tool requirements.

## Practical labs: read, change and check

Follow these after the introductory lessons. Each lab includes its own setup recap and explains the expected result.

- [Inspect a RISC-V object before linking](05-inspect-a-riscv-object.md)

## Continue with a practical source study

The RV64 example uses addw even though its registers can hold 64 bits. This lesson explains that choice by following a small result from a C-compatible function through the Assembly instruction and back to its caller.

- [Explain a word-sized result on RV64](06-explain-a-word-sized-result.md)


- [Exchange the stack pointer with a control register](07-exchange-the-stack-pointer-with-a-csr.md)

- [Map a trap frame by byte offset](08-map-a-trap-frame-by-byte-offset.md)

- [Understand stack sentinels](09-understand-stack-sentinels.md)

- [Restore state at a controlled return](10-restore-state-at-a-controlled-return.md)

- [Walk an array with loads](11-walk-an-array-with-loads.md)

- [Read branches without subtraction](12-read-branches-without-subtraction.md)

- [Preserve state across a nested call](13-preserve-state-across-a-call.md)

- [Combine shifts with OR](14-combine-shifts-with-or.md)

- [Inspect an unresolved call symbol](15-inspect-unresolved-call-symbols.md)

- [Check Assembly with a C reference](16-check-assembly-with-a-c-oracle.md)
