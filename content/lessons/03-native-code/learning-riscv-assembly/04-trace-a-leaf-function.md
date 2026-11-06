# Trace a leaf function

[Course contents](index.md) · [Previous: Preserve register values when execution is interrupted](03-preserving-interrupted-registers.md)

## Follow values through one call

After the first three lessons, return to a smaller function to connect instruction behaviour with an ABI. An ABI is an agreement about how independently compiled code passes values. Open Framework's `examples/learning/assembly/add_riscv64.S`.

The function `AddTwoAssembly` receives arguments in `a0` and `a1`. These are register names used by the calling convention. It contains:

```asm
addw a0, a0, a1
ret
```

RISC-V writes the destination first. `addw` calculates a 32-bit result on RV64 and sign-extends that result into the 64-bit destination register. With 7 and 5, the result is 12 and the upper bits are zero. With a result whose bit 31 is set, the upper bits follow that sign bit. Do not describe `addw` as a full-width 64-bit addition.

`ret` returns through the return-address convention. It does not mean stop the processor. This function is a leaf and calls no other function, so it does not need to save a return address before a nested call.

## Compare with startup code

Now open `umicom-kernel/arch/riscv64/boot.S`. Find `csrr s1, mhartid` and the stack-pointer setup. Startup code establishes conditions that an ordinary called function normally relies on. A hart is a hardware execution context in RISC-V terminology. Kernel startup is not interchangeable with a function callable from a normal host program.

## Exercise

On paper, set a0=20 and a1=3. What does a0 contain after `addw`? Next, suppose a 32-bit result has the hexadecimal pattern `80000000`. Write its full sign-extended RV64 register value.

## Explained answer

The first result is 23. The second becomes `FFFFFFFF80000000`: bit 31 is one, so all 32 new upper bits are one too. The low 32 bits keep their original pattern. This is a representation exercise, not signed C arithmetic on an overflowing expression.

Compare this with the x86 lesson's ABI table. The useful common idea is an explicit input/result contract; the register names and instructions differ. Do not run an RV64 object directly on an x86 Windows host. Use the course's existing target and emulator instructions when ready, and record the target as part of any result.

[Review the prerequisite course](../../../courses/learning-riscv/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/examples/learning/assembly/add_riscv64.S). Path: `Umicom-Applications/framework/examples/learning/assembly/add_riscv64.S`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://docs.riscv.org/reference/isa/_attachments/riscv-unprivileged.pdf). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-riscv-assembly/lessons/04-trace-a-leaf-function.html).

[Course contents](index.md) · [Previous: Preserve register values when execution is interrupted](03-preserving-interrupted-registers.md)

Sammy Hegab · Umicom Foundation · Original learning material.
