# Addresses and stored values

[Course contents](index.md) · [Previous: An eight-bit accumulator](01-an-eight-bit-accumulator.md)

## A location is different from its contents

Continue after the accumulator lesson. Memory can be pictured as numbered byte locations. An address identifies a location; the byte stored there is its content. Mixing those two ideas is a common reason an Assembly trace goes wrong.

For this exercise only, assume hexadecimal address `0100` contains decimal 6 and `0101` contains decimal 0. The `$` notation below means hexadecimal. Work on paper; these are not instructions to write an arbitrary address on your computer.

```asm
LDAA $0100
ADDA #2
STAA $0101
```

The first instruction loads the byte at address 0100, so A becomes 6. The second adds the immediate value 2, so A becomes 8. The third stores A at address 0101. Address 0100 still contains 6; address 0101 now contains 8. A store copies a value into memory; it does not rename the register or move a physical component.

## Draw the state

```text
Before: [0100: 6] [0101: 0]   A: unspecified
After:  [0100: 6] [0101: 8]   A: 8
```

`LDAA #2` would load the number 2. `LDAA $0100` loads the contents of a location. A source line's operands tell you which meaning applies. The machine encoding may use different addressing modes; choosing the intended mode is part of assembly, not an afterthought.

## Exercise and answer

Change the initial byte at 0100 to 9. The final byte at 0101 becomes 11. Explain what happens if the last instruction stores to 0100 instead: the original 9 is replaced with 11. The trace no longer preserves its input memory.

## Connect to shared software contracts

Compare this overwrite with `BtbActivityAdvance` in the activity example: its output pointer also identifies a destination. That C contract promises no output change on failure. An Assembly implementation would have to obey the same promise explicitly. Later study will introduce branches and flags so a program can check a limit before storing. The example here deliberately performs no such validation and must not be mistaken for a complete safe storage routine.

[Review the prerequisite course](../../../courses/learning-computer-architecture/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/examples/learning/assembly/add_riscv64.S). Path: `Umicom-Applications/framework/examples/learning/assembly/add_riscv64.S`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://www.bitsavers.org/components/motorola/6800/M6800_Microprocessor_Applications_Manual_1975.pdf). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-6800-assembly/lessons/02-addresses-and-stored-values.html).

[Course contents](index.md) · [Previous: An eight-bit accumulator](01-an-eight-bit-accumulator.md)

Sammy Hegab · Umicom Foundation · Original learning material.
