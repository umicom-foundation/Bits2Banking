<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-68000-assembly.md

PURPOSE:
Give learners an additional practical case for Learning Motorola 68000 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a sign-extended quick move with a byte write

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two 68000 traces begin with D0 equal to zero. One uses MOVEQ to move negative one into D0. The other moves hexadecimal FF into its low byte.

1. Trace all 32 bits of D0 after MOVEQ.
2. Trace all 32 bits after the byte write and compare the complete hexadecimal values.

**Check your result.** MOVEQ produces hexadecimal FFFFFFFF. The byte write produces hexadecimal 000000FF.

[Step-by-step course guide](../course-guides/learning-68000-assembly.md) · [Full course](../../courses/learning-68000-assembly/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-68000-assembly.md)
