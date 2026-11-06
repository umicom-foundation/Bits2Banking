# Registers and a first calculation

[Course contents](index.md) · [Next: Addresses and bytes in memory](02-addresses-and-memory.md)

## What you will learn

By the end you will be able to trace a subtraction and explain which register contains the answer. A **processor** carries out instructions. A **register** is a small named storage location inside it, used while working with values. The MC68000 has data registers D0 through D7 for this kind of work.

A **bit** is a binary digit: zero or one. Eight bits make a **byte**. Here a **word** means 16 bits and a **long word** means 32 bits. Each data register holds 32 bits. The suffix `.l` asks an instruction to work with a long word. For these first examples we use small positive whole numbers, so no rounding or fractional arithmetic is involved.

## Follow one calculation

Open the real Bits2Banking example [values.c](../../../../labs/native/first-c-programs/values.c). It starts with five tasks, records two completed tasks and calculates three remaining tasks. This fragment expresses that calculation using registers:

```asm
move.l #5, %d0
move.l #2, %d1
sub.l  %d1, %d0
```

Read the first instruction from left to right. `move` copies a value. `.l` selects 32 bits. `#5` supplies the number five directly; this is called an **immediate** value. `%d0` names the destination register. The comma separates source and destination. The percent sign is part of the GNU assembler notation used here.

The second instruction copies two into D1. The third subtracts D1 from D0 and stores the result in D0. It leaves D1's value unchanged. This is a useful habit when reading Assembly: state the destination explicitly before calculating its new value.

| After instruction | D0 | D1 | Meaning |
| --- | --- | --- | --- |
| `move.l #5, %d0` | 5 | Not yet set by this fragment | Five tasks |
| `move.l #2, %d1` | 5 | 2 | Two completed |
| `sub.l %d1, %d0` | 3 | 2 | Three remaining |

Do not assume registers start at zero. The first two instructions deliberately establish the values needed by the subtraction. Also, the fragment does not print anything: it leaves an answer in a register. The C laboratory uses `printf` to display its answer; printing requires additional runtime or device services.

## Try it yourself

1. Draw two boxes labelled D0 and D1.
2. Change the starting total to nine and the completed count to four.
3. Write the three instructions, then update the boxes one instruction at a time.
4. Predict whether D1 changes during the subtraction.

<details><summary>Check your reasoning</summary>

Use `move.l #9, %d0`, `move.l #4, %d1`, then `sub.l %d1, %d0`. D0 ends at five and D1 remains four. If your answer is negative five, you reversed the subtraction: the destination's old value is the starting value.

</details>

## Continue

You have followed values inside registers. Next you will follow values stored in memory, where every byte has an address. For the C explanation, read [Variables and simple calculations](../../../courses/learning-c/lessons/03-values-and-calculations.html).

Reference: [Motorola programmer's manual, sections 1 and 4](https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf) and [GNU assembler notation](https://sourceware.org/binutils/docs/as/M68K_002dSyntax.html). The worked example and trace are original Bits2Banking teaching material.

Sammy Hegab · Umicom Foundation · MIT for original teaching material.
