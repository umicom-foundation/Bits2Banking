<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-riscv-assembly.md

PURPOSE:
Give learners an additional practical case for Learning RISC-V Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace loads through a table of three words

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper table starts at 0x100 with 32-bit values 3, 5, and 9, one word after another.

1. Apply the array-walk lesson. Write the byte address used for each of the three loads and the running total.
2. Finish the walk after the third word. Record the final total and whether a fourth load was performed.

**Check your result.** The loads use 0x100, 0x104, and 0x108. The sum is 17 and there is no fourth load.

[Step-by-step course guide](../course-guides/learning-riscv-assembly.md) · [Full course](../../courses/learning-riscv-assembly/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-riscv-assembly.md)
