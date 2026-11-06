# Addresses and bytes in memory

[Previous: Registers and a first calculation](01-registers-and-a-calculation.md) · [Course contents](index.md) · [Next: Comparisons and a bounded loop](03-comparisons-and-loops.md)

## A location and its contents

**Memory** stores instructions and data outside the working registers. An **address** identifies a location in memory. An address is not the same thing as the value stored at that location. A numbered drawer and the paper inside it give a useful analogy: drawer number 1000 can contain the number 42.

Programmers often write addresses in **hexadecimal**, a base-16 notation using digits 0–9 followed by A–F. `0x10` means sixteen: one group of sixteen and zero units. `0x1000` means 4096. The `0x` prefix identifies the notation; it is not part of the stored value.

## Build a memory diagram

Imagine an emulator has explicitly provided readable memory at these four addresses:

| Address | Stored byte in hexadecimal | Decimal value |
| --- | --- | --- |
| 0x1000 | 00 | 0 |
| 0x1001 | 00 | 0 |
| 0x1002 | 00 | 0 |
| 0x1003 | 2A | 42 |

The MC68000 stores the most significant byte of a multi-byte number at the lowest address. This ordering is called **big-endian**. Together these four bytes represent the long-word number 0x0000002A, or 42. Address registers A0 through A7 hold addresses. Suppose A0 already contains 0x1000:

```asm
move.l %a0@, %d0
```

In this notation `%a0@` means read memory at the address in A0. The instruction reads four bytes into D0. Afterwards D0 contains 42, while A0 still contains 0x1000. Without the memory access, copying the address itself would give 4096 instead of 42.

No instruction here establishes a valid memory region. The address table is an explicit assumption for a paper exercise. Do not run fragments against guessed addresses: a real program needs a defined memory map and permission to access the region. On the original MC68000, word and long-word accesses also require an even address. 0x1000 meets that alignment requirement.

## Connect to the existing C laboratory

Read [arrays.c](../../../../labs/native/first-c-programs/arrays.c). It stores the values `{2, 1, 3}` in an array and visits them by index. An **index** selects an element; a memory address locates the bytes used to store it. C calculates element locations from the array and its element type. Do not assume that every C `int` on every platform has the same size: this Assembly exercise explicitly selects four bytes with `.l`.

## Try it yourself

1. Keep the first three bytes zero and change the last byte to `30` in hexadecimal.
2. Calculate three groups of sixteen plus zero units.
3. Predict D0 after the load, and state whether A0 has changed.
4. Explain what information would be missing before attempting a real run.

<details><summary>Check your reasoning</summary>

D0 becomes 48. A0 still contains 0x1000 because this instruction does not advance it. Before execution you need a defined target environment with a valid, readable memory region containing the stated bytes. A diagram alone does not provide that environment.

</details>

Reference: [Motorola programmer's manual, integer data formats and addressing](https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf). Address diagrams and exercises are original Bits2Banking material.

Sammy Hegab · Umicom Foundation · MIT for original teaching material.
