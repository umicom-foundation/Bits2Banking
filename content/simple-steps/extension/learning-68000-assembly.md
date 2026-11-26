<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-68000-assembly.md

PURPOSE:
Give learners an additional practical case for Learning Motorola 68000 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Split a word into two addressable bytes

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice 68000 trace stores the hexadecimal word 1234 beginning at even address 1000.

1. Write the most significant byte at the starting address using the 68000 byte order.
2. Write the next byte, then read back the two bytes in increasing address order.

**Check your result.** Address hexadecimal 1000 contains hexadecimal 12. Address hexadecimal 1001 contains hexadecimal 34.

[Step-by-step course guide](../course-guides/learning-68000-assembly.md) · [Full course](../../courses/learning-68000-assembly/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-68000-assembly.md)
