<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-riscv.md

PURPOSE:
Give learners an additional practical case for Introduction to RISC-V.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build an address breakdown for a note

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper memory map uses pages of 4096 bytes. A diagnostic record needs the page number and byte offset for address 0x2345.

1. Use the page-and-offset lesson to separate the low 12 bits from the remaining address bits.
2. Write both parts in the diagnostic record. Reconstruct the original address by combining the page base and byte offset.

**Check your result.** The page number is 0x2, the offset is 0x345, and the reconstructed address is 0x2345.

[Step-by-step course guide](../course-guides/learning-riscv.md) · [Full course](../../courses/learning-riscv/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-riscv.md)
