<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-6800-assembly.md

PURPOSE:
Give learners an additional practical case for Learning Motorola 6800 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare an immediate byte with a memory byte

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice 6800 worksheet stores hexadecimal 2F at address 0020. Two traces load A from instructions using the same written number 20.

1. Trace LDAA with hexadecimal 20 as an immediate operand.
2. Trace LDAA again with hexadecimal 20 as a direct address and compare the new accumulator values.

**Check your result.** The immediate trace loads hexadecimal 20. The direct-address trace loads hexadecimal 2F.

[Step-by-step course guide](../course-guides/learning-6800-assembly.md) · [Full course](../../courses/learning-6800-assembly/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-6800-assembly.md)
