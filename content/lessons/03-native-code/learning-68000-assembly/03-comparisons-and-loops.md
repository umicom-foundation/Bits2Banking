# Comparisons and a bounded loop

[Previous: Addresses and bytes in memory](02-addresses-and-memory.md) · [Course contents](index.md)

## Repeating a small piece of work

A **loop** repeats instructions. A useful loop needs a starting state, a condition for stopping and progress towards that condition. We will count three completed steps. Keep the count in D0 and trace every instruction on paper.

```asm
move.l #0, %d0
again:
addq.l #1, %d0
cmp.l  #3, %d0
bne    again
```

`again:` is a **label**: a name for an instruction location, not an instruction that changes a value. `addq.l #1, %d0` adds one to the 32-bit value in D0. `cmp.l #3, %d0` compares D0 with three. It records information about the comparison in condition flags and leaves D0 unchanged.

One flag is called **Z**, for zero. An equal comparison sets Z because subtracting equal values would produce zero. `bne` means branch if not equal. A **branch** changes which instruction executes next. When Z is clear, this branch goes back to `again`; when Z is set, execution continues past the fragment.

| Visit | D0 after adding one | Compare with 3 | Z | Branch back? |
| --- | --- | --- | --- | --- |
| 1 | 1 | Different | 0 | Yes |
| 2 | 2 | Different | 0 | Yes |
| 3 | 3 | Equal | 1 | No |

There are three additions. The final D0 value is three. The code after the fragment would depend on its containing program; this is not a complete executable and has no operating-system exit instruction.

## Read the related Umicom example

Open [repetition.c](../../../../labs/native/first-c-programs/repetition.c). Its `for` loop starts at one, checks `step <= 3`, prints that step and increments afterwards. It prints `Step 1`, `Step 2`, `Step 3`. Both examples make progress through three steps, but the placement of the condition matters: the C example checks before entering its body, while our Assembly fragment checks after adding one.

Read [Repeating work with a loop](../../../courses/learning-c/lessons/05-repeat-with-a-boundary.html) if the C punctuation is unfamiliar. Use that existing explanation rather than trying to learn two sets of syntax at once.

## Find a boundary mistake

1. Change the comparison's immediate value from three to five. Trace the first five visits.
2. Now consider changing it to zero while keeping the initial zero and the addition before comparison.
3. Explain why the second change does not produce zero repetitions.

<details><summary>Check your reasoning</summary>

With a target of five, five additions take place. With a target of zero, the first addition makes D0 one before the comparison. It therefore branches again. Eventually 32-bit arithmetic wraps, but waiting for that wrap is not a valid way to request zero work. A reusable loop must check for a zero count before entering its body. This is why a paper trace should include both an ordinary count and an empty case.

</details>

## Where to go next

Continue with the existing [Learning C boundary exercise](../../../courses/learning-c/lessons/18-check-a-function-at-its-boundaries.html). The same engineering habit applies to Framework services: define accepted input, show how progress is made, then check what happens at the boundary. Later Assembly study can add stack use, subroutine calls and a documented emulator laboratory.

Reference: [Motorola programmer's manual, ADDQ, CMP and Bcc](https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf). The loop and trace are original teaching examples.

Sammy Hegab · Umicom Foundation · MIT for original teaching material.
