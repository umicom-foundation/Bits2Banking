<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-riscv.md

PURPOSE:
Give learners an additional practical case for Introduction to RISC-V.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Interpret four bytes in the right order

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

In a little-endian practice memory map, addresses 0 through 3 contain 12, 34, 56 and 78 in hexadecimal.

1. Use the memory lesson to mark the lowest-address byte and its place in a 32-bit word.
2. Reconstruct the word by assigning successive bytes to increasing significance. Compare it with reading the displayed address sequence as a number.

**Check your result.** The word is 0x78563412. The physical bytes remain 12, 34, 56 and 78 at the same addresses.

[Step-by-step course guide](../course-guides/learning-riscv.md) · [Full course](../../courses/learning-riscv/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-riscv.md)
