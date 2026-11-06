# An eight-bit accumulator

[Course contents](index.md) · [Next: Addresses and stored values](02-addresses-and-stored-values.md)

## Identify the processor first

This course is about the Motorola 6800, not the Motorola 68000. The names are similar, but the processors have different instructions and programming models. Start with the computer-architecture lessons on binary, hexadecimal and memory. No emulator is required for this first paper exercise.

An accumulator is a register commonly used for arithmetic. The 6800 has 8-bit accumulators A and B. Eight bits can represent 256 patterns. Interpreted as unsigned values, those patterns represent 0 through 255. An instruction also affects condition flags; later lessons use those flags to make decisions.

## Trace immediate values

```asm
LDAA #5
ADDA #3
```

The `#` indicates an immediate value in the notation used here: the number is part of the instruction, rather than the address of a value to fetch. `LDAA` loads accumulator A. `ADDA` adds its operand to A. After the first instruction A=5. After the second A=8.

```text
Instruction      A before      A after
LDAA #5          unspecified   5
ADDA #3          5             8
```

This fragment has no reset vector, memory map or return environment. Treat it as a trace, not a complete bootable program. Assembler directives vary by tool, so we will choose an explicitly documented tool before introducing runnable projects.

## Exercise and answer

Replace 5 with 10 and 3 with 2. Expect 10, then 12. Now consider 255+1 as an unsigned 8-bit calculation: the stored low eight bits become zero and the carry flag records carry out. Zero does not mean that the mathematical sum was zero. Separating stored bits from their interpretation is essential when writing a bounded counter.

## Connect to Umicom

Read the short RISC-V addition example in Framework. It offers a comparison of the same arithmetic idea using a different register width and calling convention. Umicom's existing RISC-V example is not evidence of a 6800 Kernel port. This course teaches architecture concepts without promising unsupported hardware execution.

[Review the prerequisite course](../../../courses/learning-computer-architecture/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/examples/learning/assembly/add_riscv64.S). Path: `Umicom-Applications/framework/examples/learning/assembly/add_riscv64.S`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://www.bitsavers.org/components/motorola/6800/M6800_Microprocessor_Applications_Manual_1975.pdf). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-6800-assembly/lessons/01-an-eight-bit-accumulator.html).

[Course contents](index.md) · [Next: Addresses and stored values](02-addresses-and-stored-values.md)

Sammy Hegab · Umicom Foundation · Original learning material.
