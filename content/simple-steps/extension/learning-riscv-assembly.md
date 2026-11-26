<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-riscv-assembly.md

PURPOSE:
Give learners an additional practical case for Learning RISC-V Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a stack guard mismatch on paper

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

In the stack sentinel exercise, both guard words start as 0x5A. The final sample is 0x5A at the first boundary and 0x00 at the second.

1. Label both boundary values on a diagram of the scratch frame. Compare the first observation with the expected marker.
2. Compare the second observation with the same marker and record whether the routine should publish its result.

**Check your result.** The first guard matches. The second guard differs and the trace rejects the frame before publishing a result.

[Step-by-step course guide](../course-guides/learning-riscv-assembly.md) · [Full course](../../courses/learning-riscv-assembly/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-riscv-assembly.md)
