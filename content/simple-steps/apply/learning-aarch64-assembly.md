<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-aarch64-assembly.md

PURPOSE:
Give learners an additional practical case for Learning AArch64 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Add a two-instruction trace to a function card

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A beginner function needs to return negative two as a signed 32-bit result. The first instruction in the course pattern writes 1 to W0.

1. Trace the bitwise complement of W0 as the second instruction and write all eight hexadecimal digits of the result.
2. Use the function card to label W0's signed result and X0's complete register contents after both writes.

**Check your result.** W0 holds FFFFFFFE in hexadecimal and means negative two in 32 bits. X0 holds hexadecimal 00000000FFFFFFFE.

[Step-by-step course guide](../course-guides/learning-aarch64-assembly.md) · [Full course](../../courses/learning-aarch64-assembly/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-aarch64-assembly.md)
