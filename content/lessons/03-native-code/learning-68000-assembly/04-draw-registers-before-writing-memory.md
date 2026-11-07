<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-68000-assembly/04-draw-registers-before-writing-memory.md

PURPOSE:
  Present "Draw registers before writing memory" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Draw registers before writing memory

You can understand a short 68000 routine by keeping a written record of each register. This lesson uses the idea of a bounded counter from the existing C repetition example, then expresses a small counter using 68000 instructions.

Source to open: `Umicom-Bits2Banking/labs/native/first-c-programs/repetition.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'labs\native\first-c-programs\repetition.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'labs/native/first-c-programs/repetition.c'
```

## Understand the idea

A data register such as D0 holds a value. An immediate value, written with # in the notation here, is supplied directly in an instruction. MOVEQ places a small signed immediate into a data register. ADDQ adds a small immediate quantity. The .L suffix on ADDQ selects a long, 32-bit operation. Our example only uses 0 through 3, so arithmetic overflow does not complicate the trace. These are instruction snippets for reading; they are not a complete executable, because entry points, assemblers and output facilities depend on the chosen development environment.

```text
68000 instruction       D0 after instruction
MOVEQ #0,D0              0
ADDQ.L #1,D0             1
ADDQ.L #1,D0             2
ADDQ.L #1,D0             3
```

## Work through the lab

1. Read repetition.c to identify the counter, its starting value and the condition that stops repetition. State the purpose of a bound: it gives the work a defined stopping point.
2. On paper, create a D0 column. Read MOVEQ #0,D0 and write 0. Follow the three ADDQ.L #1,D0 instructions below, writing the new value after every line.
3. Add a second column called work completed. Match its rows to the counter values. Explain why changing the limit requires checking both the repeated operation and the stopping condition in a loop.
4. Write a tiny C reference in a separate practice file that adds one three times to an unsigned value starting at zero. Compare the expected arithmetic with the Assembly trace. Leave hardware and emulator setup to the course's introductory environment guide; do not treat this fragment as a boot program.

## Expected result

The final value is 3 and there are exactly three additions. You should be able to point to the instruction that establishes the initial state. The next step in a longer routine is to choose a documented calling convention before passing this value to other code.

## If the result differs

If your count is 4, you may have counted the initial assignment as completed work. If your assembler rejects the spelling, inspect that assembler's syntax and target selection; instruction notation in a manual is not a universal command line. Do not guess an output or return convention.

## Explain it yourself

What changes if the initial MOVEQ value is 2 and the same three additions run?

<details>
<summary>Worked explanation</summary>

D0 starts at 2, then becomes 3, 4 and 5. The number of additions is still three. Distinguishing initial state from work performed is useful when reviewing counters and retry limits in larger programs.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-68000-assembly/lessons/04-draw-registers-before-writing-memory.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](03-comparisons-and-loops.md) · [Course contents](index.md)

## Technical references

[Motorola M68000 family programmer's reference manual](https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf)

