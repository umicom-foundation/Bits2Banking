<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-aarch64-assembly.md

PURPOSE:
Give learners an additional practical case for Learning AArch64 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace why a W register write changes X

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A trace shows X0 starting at hexadecimal 0000000100000000 and then a move of 7 into W0.

1. Mark the low 32 bits written by the instruction.
2. Apply the zero-extension of the W0 write and record the complete X0 value.

**Check your result.** W0 is 7 and X0 reads hexadecimal 0000000000000007.

[Step-by-step course guide](../course-guides/learning-aarch64-assembly.md) · [Full course](../../courses/learning-aarch64-assembly/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-aarch64-assembly.md)
