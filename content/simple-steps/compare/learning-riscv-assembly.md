<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-riscv-assembly.md

PURPOSE:
Give learners an additional practical case for Learning RISC-V Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a signed word result with a full-width result

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

In a paper RV64 exercise, the source values are 0x000000007fffffff and 1.

1. Use the word-sized result lesson to trace a 32-bit word addition and sign extension into the destination.
2. Trace the same inputs through a full-width RV64 addition and compare the upper half of the registers.

**Check your result.** The word operation produces 0xffffffff80000000. The full-width operation produces 0x0000000080000000.

[Step-by-step course guide](../course-guides/learning-riscv-assembly.md) · [Full course](../../courses/learning-riscv-assembly/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-riscv-assembly.md)
