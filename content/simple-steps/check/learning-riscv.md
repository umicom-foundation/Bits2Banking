<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-riscv.md

PURPOSE:
Give learners an additional practical case for Introduction to RISC-V.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check two virtual address representations on paper

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A classroom Sv39 trace needs to recognize 0x0000003fffffffff and 0x0000004000000000 as two separate inputs.

1. Use the canonical-address lesson to read bit 38 of each operand and compare the high bits with its required sign extension.
2. Annotate the two expected validation decisions before using any later page-walk trace.

**Check your result.** The first address is canonical. The second is noncanonical because bit 38 is one with upper bits zero.

[Step-by-step course guide](../course-guides/learning-riscv.md) · [Full course](../../courses/learning-riscv/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-riscv.md)
