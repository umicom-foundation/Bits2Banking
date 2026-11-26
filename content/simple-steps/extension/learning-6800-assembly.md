<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-6800-assembly.md

PURPOSE:
Give learners an additional practical case for Learning Motorola 6800 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Store a byte and read it back on paper

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice 6800 trace starts with hexadecimal 2A in accumulator A and 00 in memory at address 0020.

1. Trace STAA at address 0020 and write the new byte at that address.
2. Clear A in the worksheet, then trace LDAA from address 0020.

**Check your result.** The memory byte becomes hexadecimal 2A after the store. The load restores A to hexadecimal 2A.

[Step-by-step course guide](../course-guides/learning-6800-assembly.md) · [Full course](../../courses/learning-6800-assembly/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-6800-assembly.md)
