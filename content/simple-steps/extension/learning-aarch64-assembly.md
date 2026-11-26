<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-aarch64-assembly.md

PURPOSE:
Give learners an additional practical case for Learning AArch64 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare the same bits with two meanings

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper AArch64 comparison uses the 32-bit pattern FFFFFFFF in W0 and the value 1 in W1.

1. Compare W0 with W1 as signed 32-bit values and mark whether the signed less-than condition holds.
2. Compare the same two bit patterns as unsigned values and mark whether the unsigned lower condition holds.

**Check your result.** Signed less-than is true because W0 means negative one. Unsigned lower is false because W0 means 4,294,967,295.

[Step-by-step course guide](../course-guides/learning-aarch64-assembly.md) · [Full course](../../courses/learning-aarch64-assembly/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-aarch64-assembly.md)
