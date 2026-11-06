# Registers and instructions

[Course contents](index.md) · [Next: A function called from C](02-a-function-called-from-c.md)

## A smaller view of a calculation

Start after Learning C's values and functions lessons. Assembly names individual processor operations. A register is a small storage location inside the processor. A mnemonic is a readable instruction name. An assembler translates those names and operands into machine instructions for a particular processor family.

This course starts with x86-64, the 64-bit member of the x86 family. It does not assume that ARM or RISC-V understands the same instructions. The following Intel-style fragment is for a paper trace; it is not a complete operating-system program:

```asm
mov eax, 7
add eax, 5
```

`eax` names a 32-bit register view. `mov` puts 7 into that destination; it does not remove 7 from anywhere. `add` replaces the destination with its old value plus 5. After the first instruction EAX is 7; after the second it is 12. The values are small enough to avoid overflow in this exercise.

## Compare notation with the real source

Open Framework's `examples/learning/assembly/add_x86_64.S`. It uses GNU AT&T notation, so registers have a `%` prefix and the source operand is written before the destination. Its `movl %ecx, %eax` copies ECX into EAX. Do not paste Intel notation into that file and expect the assembler to infer the intended language.

The `.S` extension also allows the C preprocessor to select platform-specific sections. Lines beginning with `#if` are build-time choices, not instructions executed by the processor. This distinction explains why two different argument-register sequences appear in one file.

## Exercise and answer

Trace `mov eax, 9` followed by `add eax, 4`. Write the register value after each instruction: 9, then 13. Now explain why reversing the two operands of a move changes its meaning.

To run Assembly later you will need an assembler, a matching target and a calling environment. For this lesson, a correct register trace is the expected result. It is safer and more useful than running an incomplete fragment with no defined entry or return. The next lesson explains the C-to-Assembly boundary used by the existing Umicom example.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/examples/learning/assembly/add_x86_64.S). Path: `Umicom-Applications/framework/examples/learning/assembly/add_x86_64.S`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://www.nasm.us/doc/nasm03.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-x86-assembly/lessons/01-registers-and-instructions.html).

[Course contents](index.md) · [Next: A function called from C](02-a-function-called-from-c.md)

Sammy Hegab · Umicom Foundation · Original learning material.
